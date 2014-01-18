#include "stdafx.h"

#include "puzzlesolver.h"
#include "puzzleboard.h"
#include "exceptions.h"
#include "puzzleshuffler.h"
#include <iostream>

using namespace std;
using namespace board;

PuzzleSolver::PuzzleSolver (const Dimension2D &dim) :
    dimensionOfBoards(new Dimension2D(dim))   ,
    boardToSolve(0),
    stateManager(new StateManager()),
    steps(new vector<board::SLIDE_DIRECTIONS> )
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
    int count = 0;
    while (!isSolved())
    {
        auto states = getAvailableStates();
        for (u_int i = 0; i<states.size(); i++)
        {
            if (*(states[i]->currentBoard) != *getCurrentState()->currentBoard)
                stateManager->addState(states[i]);
        }
        stateManager->setNextCurrentState();
        count++;
        if (count > 600000)
            throw Exception("over 60000");
        cout << "States: " << stateManager->getNumStates() << endl;
    }

}

void PuzzleSolver::setBoardToSolve(PuzzleBoard &b) throw()
{
    boardToSolve = b.clone();
    setGoalBoard();
}


const std::vector<board::SLIDE_DIRECTIONS> PuzzleSolver::getResult()
{
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

PuzzleBoardState::~PuzzleBoardState()
{
}


PuzzleBoardState::PuzzleBoardState(u_int movesMadeSoFar,  std::shared_ptr<PuzzleBoardState> cameFrom, board::PuzzleBoard & thisStateBoardAlignment, std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState):
    cameFrom(cameFrom),
    currentBoard(thisStateBoardAlignment.clone()),
    movesMadeSoFar(movesMadeSoFar),
    hammingPriority(calculateHammingPriority()),
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
