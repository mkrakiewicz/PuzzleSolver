#include "puzzlesolver.h"
#include "puzzleboard.h"
#include "exceptions.h"

using namespace board;

PuzzleSolver::PuzzleSolver()
    :boardToSolve(0),result(0)
{
}

void PuzzleSolver::solve()
{
    if (!boardToSolve)
        return;

}

void PuzzleSolver::setBoard(std::shared_ptr<PuzzleBoard> b) throw()
{
    if (b == 0)
        throw new Exception("Trying to set NULL Board");
    boardToSolve = b;
}

std::shared_ptr<PuzzleBoard> PuzzleSolver::getResult()
{
    if (result == 0)
    {
        if (boardToSolve == 0)
        {
            std::shared_ptr<PuzzleBoard> p(new EmptyBoard(boardToSolve->getDimensions()));
            return p;
        } else
        {
            return boardToSolve;
        }
    }
    return result;
}
