#include "puzzle.h"
#include <iostream>

using namespace std;


Puzzle::~Puzzle(){}

PUZZLE_TYPES EmptyPuzzle::getType()
{
    return PUZZLE_TYPES::EMPTY;
}

EmptyPuzzle::~EmptyPuzzle(){}

void EmptyPuzzle::print()
{
    std :: cout << "X";
}

shared_ptr<Puzzle> EmptyPuzzle::clone() const
{
    return shared_ptr<Puzzle>(new EmptyPuzzle(*this));
}

bool EmptyPuzzle::isEqual(Puzzle *obj)
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


bool PuzzleObject::isEqual(Puzzle *obj)
{
    if (obj->getType() != OBJECT)
        return false;
    return true;
}

IntPuzzle :: IntPuzzle(int value):
    Value(value)
{
}

void IntPuzzle ::print()
{
    std :: cout << Value;
}


shared_ptr<Puzzle> IntPuzzle ::clone() const
{
    return shared_ptr<Puzzle>(new IntPuzzle(*this));
}

IntPuzzle ::~IntPuzzle(){}


bool IntPuzzle ::isEqual(Puzzle *obj)
{
    if (!PuzzleObject::isEqual(obj))
        return false;

    if (Value == ( (IntPuzzle*)obj )->Value)
        return true;

    return false;
}


