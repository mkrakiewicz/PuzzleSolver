#include "position2d.h"
#include "puzzleboard.h"

using namespace boards;

Position2D::Position2D(int x, int y):
    X(x),Y(y)
{
}


bool Position2D::positionExceedsBounds(const Dimension2D &d)
{
    if (X >= (int)d.horizontalSize || Y >= (int)d.verticalSize)
        return true;
    return false;
}

