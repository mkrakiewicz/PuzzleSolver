#include "stdafx.h"

#include "qpuzzlecreator.h"
#include "qpuzzle.h"
#include "config.h"
#include "puzzle.h"
#include "puzzleboard.h"
#include "exceptions.h"
#include <QWidget>
#include <qpuzzleboard.h>

using namespace board;
using namespace puzzle;
using namespace std;


QPuzzleCreator::QPuzzleCreator():
    realBoard(0),
    parentBoard(0),
    parentObject(0)
{

}

QLabelPuzzle* QPuzzleCreator::createPuzzle(const IntPuzzle &puzzle)
{

    if (realBoard == 0)
        throw Exception("Real board not set!");

    QLabelPuzzle* p = 0;
    if (parentObject)
        p = new QLabelPuzzle(parentObject);
    else
         p = new QLabelPuzzle();


    {
        auto  p_ = realBoard->getPuzzle(puzzle);

        p->setInnerPuzzle((IntPuzzle*)p_);
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

