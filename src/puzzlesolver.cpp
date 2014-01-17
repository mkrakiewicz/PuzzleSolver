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
    result(0),
    dimensionOfBoards(new Dimension2D(dim))
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

std::shared_ptr<PuzzleBoard> PuzzleSolver::getResult()
{
    if (result == 0)
    {
        if (boardToSolve == 0)
        {

            std::shared_ptr<PuzzleBoard> p(new EmptyBoard( *dimensionOfBoards ) );
            return p;
        } else
        {
            return boardToSolve;
        }
    }
    return result;
}

std::vector<SolveStep> PuzzleSolver::getSolveSteps()
{
    auto a = *steps;
    return  a;
}

int PuzzleSolver::calculateHammingPriorityFor(std::shared_ptr<PuzzleBoardState> state)
{
    int misaligned = state->currentBoardState->getNumberOfPuzzlesInWrongPosition();
    return misaligned + state->movesMadeSoFar;
}

void PuzzleSolver::_debug_steps(PuzzleShuffler &p)
{
    auto s = p.getStepHistory();
    for (int i = (s.size() -1); i>=0; i--)
    {
        steps->push_back(SolveStep(operator -(s[i].begin()->first)));
    }
}

//void PuzzleSolver::_debug_set_next_step()
//{
//}


SolveStep::SolveStep(SLIDE_DIRECTIONS slideDirection):slideDirection(slideDirection)
{
}


PuzzleBoardState::PuzzleBoardState(u_int movesMadeSoFar,  const board::PuzzleBoard & currentBoardState):
    movesMadeSoFar(movesMadeSoFar),
    currentBoardState(currentBoardState.clone())
{

}
