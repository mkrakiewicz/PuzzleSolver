#include "stdafx.h"

#include "puzzlecreator.h"
#include "qpuzzle.h"
#include "config.h"
#include "puzzle.h"
#include <QWidget>
#include <qpuzzleboard.h>

using namespace puzzle;
using namespace std;


PuzzleCreator::PuzzleCreator():
    parentBoard(0),
    parentObject(0)
{

}

QLabelPuzzle* PuzzleCreator::createPuzzle(u_int ID)
{
    QLabelPuzzle* p = 0;
    if (parentObject)
        p = new QLabelPuzzle();
    {
        std::shared_ptr <puzzle::IntPuzzle> tmp(new IntPuzzle(ID));
        p->setInnerPuzzle(tmp);
    }

    p->setText(QString::number(p->getInnerPuzzle()->Value));
    QRect tmp = p->geometry();
    tmp.setWidth(puzzleSize);
    tmp.setHeight(puzzleSize);
    p->setGeometry(tmp);
    p->move(5+xOffsetMultiplier*moveBy,5+yOffsetMultiplier*moveBy);
    p->setFrameShape(QFrame::Shape::Panel);
    if (parentBoard)
        p->setParrentBoard(parentBoard);

    p->show();
    if (parentObject)
        p->setParent(parentObject);
    p->setAlignment(Qt::AlignCenter);
    return p;
}

