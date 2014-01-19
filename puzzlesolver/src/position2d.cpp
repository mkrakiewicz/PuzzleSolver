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
    if ((X < toCompare.X) && (Y < toCompare.Y))
        return true;

    int thisSum = X+Y , otherSum = toCompare.X+toCompare.Y;

    if (thisSum < otherSum)
        return true;

    return false;
}

std::shared_ptr<Position2D> Position2D::clone() const
{
    return std::shared_ptr<Position2D>(new Position2D(*this));
}

string Position2D::toString()
{
    stringstream s;
    s << "X: " << X << ", Y: " << Y << endl;
    return s.str();
}
