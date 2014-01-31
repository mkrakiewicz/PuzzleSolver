#include "stdafx.h"

#include "puzzle.h"
#include <string>
#include <sstream>

using namespace std;

namespace puzzle {

bool Puzzle::operator ==(Puzzle &toCompare)
{
    return this->isEqual(toCompare);
}

bool Puzzle::operator !=( Puzzle &toCompare)
{
    return !this->isEqual(toCompare);
}

Puzzle::~Puzzle(){}

PUZZLE_TYPES EmptyPuzzle::getType()
{
    return PUZZLE_TYPES::EMPTY;
}

EmptyPuzzle::~EmptyPuzzle(){}

string EmptyPuzzle::toString()
{
    return string("[X]");
}

Puzzle* EmptyPuzzle::clone()
{
    return new EmptyPuzzle(*this);
}

bool EmptyPuzzle::isEqual( Puzzle &obj)
{
    if (obj.getType() != EMPTY)
        return false;
    return true;
}



PUZZLE_TYPES PuzzleObject::getType()
{
    return PUZZLE_TYPES::OBJECT;
}

PuzzleObject::~PuzzleObject(){}


bool PuzzleObject::isEqual( Puzzle &obj)
{
    if (obj.getType() != OBJECT)
        return false;
    return true;
}

IntPuzzle :: IntPuzzle(int value):
    Value(value)
{
}

string IntPuzzle ::toString()
{
    stringstream s;
    s << "[" <<  Value << "]";
    return s.str();
}


Puzzle* IntPuzzle ::clone()
{
    return new IntPuzzle(*this);
}

IntPuzzle ::~IntPuzzle(){}


bool IntPuzzle ::isEqual( Puzzle &obj)
{
    if (!PuzzleObject::isEqual(obj))
        return false;

    if (Value == ( (IntPuzzle&)obj ).Value)
        return true;

    return false;
}

}
