#include "position2d.h"
#include "puzzleboard.h"
#include<iostream>
#include<sstream>
#include<string>

using namespace board;
using namespace std;


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

string Position2D::toString()
{
    stringstream s;
    s << "X: " << X << ", Y: " << Y << endl;
    return s.str();
}
