#include "stdafx.h"

#include "puzzle.h"
#include <string>
#include <sstream>

using namespace std;

namespace puzzle {

bool Puzzle::operator ==(const Puzzle &toCompare)
{
    return this->isEqual(toCompare);
}

bool Puzzle::operator !=(const Puzzle &toCompare)
{
    return !this->isEqual(toCompare);
}

Puzzle::~Puzzle(){}

PUZZLE_TYPES EmptyPuzzle::getType() const
{
    return PUZZLE_TYPES::EMPTY;
}

EmptyPuzzle::~EmptyPuzzle(){}

string EmptyPuzzle::toString()
{
    return string("[X]");
}

std::shared_ptr<Puzzle> EmptyPuzzle::clone() const
{
    return std::make_shared<EmptyPuzzle>(*this);
}

bool EmptyPuzzle::isEqual(const Puzzle &toCompare)
{
    if (toCompare.getType() != EMPTY)
        return false;
    return true;
}



PUZZLE_TYPES PuzzleObject::getType() const
{
    return PUZZLE_TYPES::OBJECT;
}

PuzzleObject::~PuzzleObject(){}


bool PuzzleObject::isEqual(const Puzzle &toCompare)
{
    if (toCompare.getType() != OBJECT)
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


std::shared_ptr<Puzzle> IntPuzzle::clone() const
{
    return std::make_shared<IntPuzzle>(*this);
}

IntPuzzle ::~IntPuzzle(){}


bool IntPuzzle ::isEqual(const Puzzle &toCompare)
{
    if (!PuzzleObject::isEqual(toCompare))
        return false;

    if (Value == ( (const IntPuzzle&)toCompare ).Value)
        return true;

    return false;
}

}
