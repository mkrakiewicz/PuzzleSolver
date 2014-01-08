#include "puzzleshuffler.h"
#include "puzzleboard.h"

using namespace boards;

PuzzleShuffler::PuzzleShuffler():
    steps(3), initial(0), result(0)
{
}

void PuzzleShuffler::setInitialBoard(PuzzleBoard &b)
{
    initial = std::shared_ptr<PuzzleBoard>(b.clone());
}

void PuzzleShuffler::setSteps(int steps)
{
    this->steps = steps;
}

void PuzzleShuffler::shuffle()
{
}

std::shared_ptr<PuzzleBoard> PuzzleShuffler::getResult()
{
    return initial;
}
