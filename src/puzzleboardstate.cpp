#include "puzzleboardstate.h"

PuzzleBoardState::PuzzleBoardState(int sizeX, int sizeY):
    sizeX(sizeX), sizeY(sizeY)
{
}

int PuzzleBoardState::getHorizontalSize() const
{
    return sizeX;
}


int PuzzleBoardState::getVerticalSize() const
{
    return sizeY;
}



