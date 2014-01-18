#include "stdafx.h"

#include "puzzlesolver.h"
#include "puzzleboard.h"
#include "exceptions.h"
#include "puzzleshuffler.h"

using namespace std;
using namespace board;

PuzzleSolver::PuzzleSolver (const Dimension2D &dim) :
    dimensionOfBoards(new Dimension2D(dim))   ,
    boardToSolve(0),
    stateManager(new StateManager()),
    steps(new vector<SolveStep> )
{
}

void PuzzleSolver::newSearch()
{
    stateManager->clear();
    shared_ptr<PuzzleBoardState> s(new PuzzleBoardState(0,0,*boardToSolve));
    stateManager->addState(s);
}

void PuzzleSolver::solve()
{
    if (!boardToSolve)
        return;

}

void PuzzleSolver::setBoardToSolve(PuzzleBoard &b) throw()
{
    boardToSolve = b.clone();
}


std::vector<SolveStep> PuzzleSolver::getSolveSteps()
{
    auto a = *steps;
    return  a;
}

std::shared_ptr<PuzzleBoardState> StateManager::popStateWithLowestPriority()
{

    auto it = stateList.begin();
    if (it == stateList.end())
        return std::shared_ptr<PuzzleBoardState>(0);

    auto min = it;
    for (; it!=stateList.end(); it++)
    {
        if ((*it)->hammingPriority < (*min)->hammingPriority)
            min = it;
    }
    auto result = *min;
    stateList.erase(min);
    return result;
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


SolveStep::SolveStep(SLIDE_DIRECTIONS slideDirection):slideDirection(slideDirection)
{
}

SolveStep::~SolveStep()
{
}


PuzzleBoardState::PuzzleBoardState(u_int movesMadeSoFar,  std::shared_ptr<PuzzleBoardState> cameFrom, board::PuzzleBoard & thisStateBoardAlignment):
    cameFrom(cameFrom),
    currentBoard(thisStateBoardAlignment.clone()),
    movesMadeSoFar(movesMadeSoFar),
    hammingPriority(calculateHammingPriority())

{

}


StateManager::StateManager()

{
}

void StateManager::addState(std::shared_ptr<PuzzleBoardState> s)
{
    this->stateList.push_back(s);
}

StateManager::~StateManager()
{
}
