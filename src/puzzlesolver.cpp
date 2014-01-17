#include "stdafx.h"

#include "puzzlesolver.h"
#include "puzzleboard.h"
#include "exceptions.h"
#include "puzzleshuffler.h"

using namespace std;
using namespace board;

PuzzleSolver::PuzzleSolver (const Dimension2D &dim) :
    steps(new vector<SolveStep> ),
    boardToSolve(0),
    dimensionOfBoards(new Dimension2D(dim))
{
}

void PuzzleSolver::newSearch()
{

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

std::shared_ptr<PuzzleBoardState> PuzzleSolver::getStateWithHighestPriority()
{
    return std::shared_ptr<PuzzleBoardState>(0);
}

int PuzzleBoardState::calculateHammingPriorityFor(board::PuzzleBoard& board)
{
    int misaligned = board.getNumberOfPuzzlesInWrongPosition();
    return misaligned + this->movesMadeSoFar;
}


SolveStep::SolveStep(SLIDE_DIRECTIONS slideDirection):slideDirection(slideDirection)
{
}


PuzzleBoardState::PuzzleBoardState(u_int movesMadeSoFar,  std::shared_ptr<PuzzleBoardState> cameFrom, board::PuzzleBoard & currentBoardState):
    movesMadeSoFar(movesMadeSoFar),
    cameFrom(cameFrom),
    currentBoard(currentBoardState.clone())
{

}
