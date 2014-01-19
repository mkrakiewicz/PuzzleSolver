#include "stdafx.h"

#include "puzzle.h"
#include <string>
#include <sstream>

using namespace std;

namespace puzzle {

bool Puzzle::operator ==(Puzzle &toCompare) const
{
    return this->isEqual(&toCompare);
}

bool Puzzle::operator !=(Puzzle &toCompare)
{
    return !this->isEqual(&toCompare);
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

shared_ptr<Puzzle> EmptyPuzzle::clone() const
{
    return shared_ptr<Puzzle>(new EmptyPuzzle(*this));
}

bool EmptyPuzzle::isEqual(Puzzle *obj) const
{
    if (obj->getType() != EMPTY)
        return false;
    return true;
}



PUZZLE_TYPES PuzzleObject::getType()
{
    return PUZZLE_TYPES::OBJECT;
}

PuzzleObject::~PuzzleObject(){}


bool PuzzleObject::isEqual(Puzzle *obj) const
{
    if (obj->getType() != OBJECT)
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


shared_ptr<Puzzle> IntPuzzle ::clone() const
{
    return shared_ptr<Puzzle>(new IntPuzzle(*this));
}

IntPuzzle ::~IntPuzzle(){}


bool IntPuzzle ::isEqual(Puzzle *obj) const
{
    if (!PuzzleObject::isEqual(obj))
        return false;

    if (Value == ( (IntPuzzle*)obj )->Value)
        return true;

    return false;
}

}
