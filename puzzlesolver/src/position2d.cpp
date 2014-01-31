#include "stdafx.h"
#include "position2d.h"
#include "puzzleboard.h"
#include<iostream>
#include<sstream>
#include<string>
#include<memory>


using namespace board;
using namespace std;


Position2D::Position2D(int x, int y):
    X(x),Y(y)
{
}


bool Position2D::operator ==(const Position2D &toCompare) const
{
    if (X != toCompare.X)
        return false;
    if (Y != toCompare.Y)
        return false;
    return true;
}

bool Position2D::operator !=(const Position2D &toCompare) const
{
    return !operator ==(toCompare);
}

bool Position2D::operator <(const Position2D &toCompare) const
{
    if (X < toCompare.X) return true;
    if (toCompare.X < X) return false;
    if (Y < toCompare.Y) return true;
    if (toCompare.Y < Y) return false;
    return false;
}

Position2D *Position2D::clone() const
{
    return new Position2D(*this);
}

string Position2D::toString()
{
    stringstream s;
    s << "X: " << X << ", Y: " << Y << endl;
    return s.str();
}
