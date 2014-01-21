#include "stdafx.h"

#include "puzzleqobject.h"
#include "puzzle.h"

using namespace puzzle;

PuzzleQObject::PuzzleQObject(QWidget *parent) :
    QLabel(parent),
    puzzle(0)

{
}

void PuzzleQObject::setPuzzle(std::shared_ptr<puzzle::IntPuzzle> puzzle)
{
    this->puzzle = puzzle;
}

const std::shared_ptr<IntPuzzle> PuzzleQObject::getPuzzle()
{
    if (puzzle)
        return puzzle;
    return std::shared_ptr<IntPuzzle>(0);
}

int PuzzleQObject::getID()
{ll
    if (puzzle)
        return puzzle->Value;
    return -1;
}


QLabelPuzzle::QLabelPuzzle(QWidget *parent):
    PuzzleQObject(parent)
{
}
