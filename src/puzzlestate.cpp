#include "puzzlestate.h"


Point::Point(int x, int y):
    x(x),y(y)
{
}

void Point::setNewPosition(Point p)
{
    this->x = p.x;
    this->y = p.y;
}
