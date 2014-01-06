#include <puzzleboardstate.h>

TwoDimensions::TwoDimensions(int sizeX, int sizeY):
    sizeX(sizeX), sizeY(sizeY)
{
}

int TwoDimensions::getHorizontalSize() const
{
    return sizeX;
}


int TwoDimensions::getVerticalSize() const
{
    return sizeY;
}


void PointStateContainer::setState(PointState<T> pstate)
{
}

void PointStateContainer::getStateAt(Point p)
{
}


