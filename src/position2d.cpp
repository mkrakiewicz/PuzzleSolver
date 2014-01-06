#include "position2d.h"

Position2D::Position2D(int x, int y):
    X(x),Y(y)
{
}


bool Position2D::positionExceedsBounds(const Dimension2D &d)
{
    if (X >= d.horizontalSize || Y >= d.verticalSize)
        return true;
    return false;
}
