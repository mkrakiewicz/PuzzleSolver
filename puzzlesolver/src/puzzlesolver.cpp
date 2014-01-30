#include "stdafx.h"

#include "puzzlesolver.h"
#include "puzzleboard.h"
#include "exceptions.h"
#include "puzzleshuffler.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace board;

PuzzleSolver::PuzzleSolver () :
    boardToSolve(0),
    stateManager(new StateManager()),
    steps(new vector<board::SLIDE_DIRECTIONS> ),
    statesChecked(0)
{
    priorityFunction = MANHATTAN;
}

void PuzzleSolver::newSearch()
{
    stateManager->clear();
    PuzzleBoardStateParams p;
    p.currentBoard = boardToSolve;
    p.priority = calculatePriority(*boardToSolve,0);
    shared_ptr<PuzzleBoardState> s(new PuzzleBoardState(p));
    stateManager->addState(s);
    stateManager->setNextCurrentState();
    steps->clear();
}

void PuzzleSolver::solve()
{
    if (!boardToSolve)
        return;

    newSearch();
    this->statesChecked = 0;
    while (!isSolved())
    {
        this->statesChecked++;
        stateManager->transferToClosedList(getCurrentState());
        auto states = getAvailableStates();
        for (u_int i = 0; i<states.size(); i++)
        {
                stateManager->addState(states[i]);
        }
        stateManager->setNextCurrentState();
        if (statesChecked > stateCheckLimit) {
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
    const u_int moveCount = this->getCurrentState()->movesMadeSoFar +1;

    for (u_int i=0; i<PuzzleBoard::directions.size(); i++)
    {
        auto tmpBoard = currentBoard->clone();
        if (tmpBoard->slidePuzzle(PuzzleBoard::directions[i]))
        {
            std::shared_ptr<board::SLIDE_DIRECTIONS> dptr(new board::SLIDE_DIRECTIONS(PuzzleBoard::directions[i]));
            PuzzleBoardStateParams p;
            p.movesMadeSoFar = moveCount;
            p.currentBoard = tmpBoard;
            p.directionToThisState = dptr;
            p.cameFrom = getCurrentState();
            p.priority = calculatePriority(*tmpBoard,moveCount);
            std::shared_ptr<PuzzleBoardState> tmp(new PuzzleBoardState(p));
            if (stateManager->hasThisStateBeenChecked(tmp))
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
//    openStateList.erase(s);

}
const std::shared_ptr<PuzzleBoardState > StateManager::getCurrentState()
{
    return currentState;
}

u_int StateManager::getNumStates()
{
    return openStateList.size();
}

bool StateManager::hasThisStateBeenChecked(shared_ptr<PuzzleBoardState> state)
{
    auto board = state->currentBoard;

    for(auto it = closedList.begin(); it!= closedList.end(); ++it)
    {
        auto tmpBoard = (*it)->currentBoard;
        if (*tmpBoard == *board)
           return true;
    }

    return false;
}

void StateManager::transferToClosedList(std::shared_ptr<PuzzleBoardState> state)
{
    auto s = openStateList.end();
    for(auto it = openStateList.begin(); it!= openStateList.end(); ++it)
    {
        if (*it == state)
            s = it;
    }
    closedList.insert(*s);
    if (s != openStateList.end())
        openStateList.erase(s);
}

StateListIterator StateManager::getStateWithLowestPriority()
{
       auto it = openStateList.begin();

       auto min = it;
       for (; it!=openStateList.end(); it++)
       {
           if ((*it)->priority < (*min)->priority)
               min = it;
       }
       return min;
}

void StateManager::clear()
{
    openStateList.clear();
    closedList.clear();
    currentState = 0;
}


PuzzleBoardState::~PuzzleBoardState()
{
}


PuzzleBoardState::PuzzleBoardState(const PuzzleBoardStateParams &params):
    cameFrom(params.cameFrom),
    currentBoard(params.currentBoard->clone()),
    movesMadeSoFar(params.movesMadeSoFar),
    priority(params.priority),
    directionToThisState(params.directionToThisState)

{

}


StateManager::StateManager():
   currentState(0)
{
}

void StateManager::addState(std::shared_ptr<PuzzleBoardState> s)
{
    openStateList.push_back(s);
}

StateManager::~StateManager()
{
}

u_int PuzzleSolver::getStatesChecked() const
{
    return statesChecked;
}





void PuzzleSolver::setStateCheckLimit(const u_int &value)
{
    stateCheckLimit = value;
}

int PuzzleSolver::calculatePriority(PuzzleBoard &b, int moveCount)
{
    switch(priorityFunction)
    {
        case HAMMING:
            return b.calculateHammingPriority(moveCount);
        case MANHATTAN:
            return b.calculateManhattanPriority(moveCount);
    }
    return 0;
}


PuzzleBoardStateParams::PuzzleBoardStateParams():
    cameFrom(0),
    currentBoard(0),
    movesMadeSoFar(0),
    priority(0),
    directionToThisState(0)
{
}


void PuzzleSolver::setPriorityFunction(const PriorityFunction &value)
{
    priorityFunction = value;
}
