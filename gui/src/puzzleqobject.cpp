#include "puzzleqobject.h"

PuzzleQObject::PuzzleQObject(QWidget *parent) :
    QLabel(parent)

{
}


QLabelPuzzle::QLabelPuzzle(QWidget *parent):
    PuzzleQObject(parent)
{
}
