#include "stdafx.h"

#include "puzzlesolver.h"
#include "puzzleboard.h"
#include "exceptions.h"
#include "puzzleshuffler.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;
using namespace board;

PuzzleSolver::PuzzleSolver () :
    boardToSolve(0),
    stateManager(new StateManager()),
    steps(new vector<board::SLIDE_DIRECTIONS> ),
    statesChecked(0)
{
}

void PuzzleSolver::newSearch()
{
    stateManager->clear();
    shared_ptr<PuzzleBoardState> s(new PuzzleBoardState(0,0,*boardToSolve,0));
    stateManager->addState(s);
    stateManager->setNextCurrentState();
    steps->clear();
}

void PuzzleSolver::solve()
{
    if (!boardToSolve)
        return;

    newSearch();
    statesChecked = 0;
    while (!isSolved())
    {
        statesChecked++;
        stateManager->setThisStateAsChecked();
        auto states = getAvailableStates();
        for (u_int i = 0; i<states.size(); i++)
        {
            if (*(states[i]->currentBoard) != *getCurrentState()->currentBoard)
                stateManager->addState(states[i]);
        }
        stateManager->setNextCurrentState();
        if (stateManager->getNumStates() > stateCheckLimit) {
            stringstream s;
            s << "Over " << stateCheckLimit << " states checked.";
            throw Exception(s.str().c_str());
        }
    }

}

void PuzzleSolver::setBoardToSolve(PuzzleBoard &b)
{
    boardToSolve = b.clone();
    setGoalBoard();
}


const std::vector<board::SLIDE_DIRECTIONS> PuzzleSolver::getResult()
{
    if (boardToSolve == 0){
        std::vector<board::SLIDE_DIRECTIONS> a;
        return a;
    }

    if (steps->size() == 0)
    {
        recursiveAddSteps(getCurrentState());
        std::reverse(steps->begin(), steps->end());

    }
    return *steps;
}

const std::shared_ptr<PuzzleBoardState> PuzzleSolver::getCurrentState()
{
    return stateManager->getCurrentState();
}

const std::vector<std::shared_ptr<PuzzleBoardState> > PuzzleSolver::getAvailableStates()
{

    vector < std::shared_ptr<PuzzleBoardState> > states;
    const auto currentBoard = this->getCurrentState()->currentBoard;
    const u_int nextMoveCount = this->getCurrentState()->movesMadeSoFar + 1;

    for (u_int i=0; i<PuzzleBoard::directions.size(); i++)
    {
        auto tmpBoard = currentBoard->clone();
        if (tmpBoard->slidePuzzle(PuzzleBoard::directions[i]))
        {
            std::shared_ptr<board::SLIDE_DIRECTIONS> dptr(new board::SLIDE_DIRECTIONS(PuzzleBoard::directions[i]));
            std::shared_ptr<PuzzleBoardState> tmp(new PuzzleBoardState(nextMoveCount,this->getCurrentState(),*tmpBoard,dptr));
            if (stateManager->hasThisStateBeenChecked(*tmp))
                continue;
            states.push_back(tmp);
        }
    }

    return states;
}

void PuzzleSolver::setGoalBoard()
{
    auto b = boardToSolve->clone();
    b->setCorrectAlignment();
    goalBoard = b;
}

bool PuzzleSolver::isSolved()
{
    if (*(getCurrentState()->currentBoard) == *goalBoard)
        return true;
    return false;
}

void PuzzleSolver::recursiveAddSteps(std::shared_ptr<PuzzleBoardState> parent)
{

    if (parent->directionToThisState != 0)
    {
        steps->push_back(*parent->directionToThisState);
        if (parent->cameFrom !=0)
        {
            recursiveAddSteps(parent->cameFrom);
        }
    }

}

void StateManager::setNextCurrentState()
{
    auto s = getStateWithLowestPriority();
    currentState = *s;
    stateList.erase(s);

}
const std::shared_ptr<PuzzleBoardState > StateManager::getCurrentState()
{
    return currentState;
}

u_int StateManager::getNumStates()
{
    return stateList.size();
}

bool StateManager::hasThisStateBeenChecked(const PuzzleBoardState &state)
{
    for(u_int i=0; i<alreadyChecked.size(); i++)
        if ((alreadyChecked[i])->currentBoard == state.currentBoard)
            return true;
    return false;
}

StateListIterator StateManager::getStateWithLowestPriority()
{

    auto it = stateList.begin();

    auto min = it;
    for (; it!=stateList.end(); it++)
    {
        if ((*it)->hammingPriority < (*min)->hammingPriority)
            min = it;
    }
    return min;
}

void StateManager::clear()
{
    stateList.clear();
}

int PuzzleBoardState::calculateHammingPriority()
{
    int misaligned = currentBoard->getNumberOfPuzzlesInWrongPosition();
    return misaligned + movesMadeSoFar;
}

int PuzzleBoardState::calculateManhattanPriority()
{
    int distance = abs(x1-x0) + abs(y1-y0);
}

int PuzzleBoardState::calculatePriority()
{
}

PuzzleBoardState::~PuzzleBoardState()
{
}


PuzzleBoardState::PuzzleBoardState(u_int movesMadeSoFar,  std::shared_ptr<PuzzleBoardState> cameFrom, board::PuzzleBoard & thisStateBoardAlignment, std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState):
    cameFrom(cameFrom),
    currentBoard(thisStateBoardAlignment.clone()),
    movesMadeSoFar(movesMadeSoFar),
    priority(calculateHammingPriority()),
    directionToThisState(directionToThisState)

{

}


StateManager::StateManager():
   currentState(0)
{
}

void StateManager::addState(std::shared_ptr<PuzzleBoardState> s)
{
    this->stateList.push_back(s);
}

StateManager::~StateManager()
{
}

u_int PuzzleSolver::getStatesChecked() const
{
    return statesChecked;
}


void StateManager::setThisStateAsChecked()
{
    alreadyChecked.push_back(currentState);
}


void PuzzleSolver::setStateCheckLimit(const u_int &value)
{
    stateCheckLimit = value;
}
