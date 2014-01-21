#include "stdafx.h"

#include "qpuzzle.h"
#include "puzzle.h"

using namespace puzzle;

QPuzzle::QPuzzle(QWidget *parent) :
    QLabel(parent),
    puzzle(0)

{
}

void QPuzzle::setPuzzle(std::shared_ptr<puzzle::IntPuzzle> puzzle)
{
    this->puzzle = puzzle;
}

const std::shared_ptr<IntPuzzle> QPuzzle::getPuzzle()
{
    if (puzzle)
        return puzzle;
    return std::shared_ptr<IntPuzzle>(0);
}

int QPuzzle::getID()
{
    if (puzzle)
        return puzzle->Value;
    return -1;
}


QLabelPuzzle::QLabelPuzzle(QWidget *parent):
    QPuzzle(parent)
{
}
