#include "stdafx.h"

#include "puzzlecreator.h"
#include "qpuzzle.h"
#include "config.h"
#include "puzzle.h"
#include <QWidget>

using namespace puzzle;
using namespace std;


PuzzleCreator::PuzzleCreator():
    parentObject(0)
{

}

std::shared_ptr<QLabelPuzzle> PuzzleCreator::createPuzzle(u_int ID)
{
    std::shared_ptr <QLabelPuzzle> p ( new QLabelPuzzle());

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

    p->show();
    if (parentObject)
        p->setParent(parentObject);
    p->setAlignment(Qt::AlignCenter);
    return p;
}

