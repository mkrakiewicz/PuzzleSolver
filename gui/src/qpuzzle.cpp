#include "stdafx.h"

#include "qpuzzle.h"
#include "puzzle.h"
#include <QPropertyAnimation>
#include "qpuzzleboard.h"

using namespace puzzle;
using namespace board;

QPuzzle::QPuzzle(QWidget *parent) :
    QLabel(parent),
    puzzle(0),
    parentBoard(0)

{
    connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
}

void QPuzzle::setInnerPuzzle(puzzle::IntPuzzle* puzzle)
{
    this->puzzle = puzzle;
}

void QPuzzle::setParrentBoard(QPuzzleBoard* p)
{
    parentBoard = p;
}

const IntPuzzle* QPuzzle::getInnerPuzzle()
{
    if (puzzle)
        return puzzle;
    return 0;
}

int QPuzzle::getID()
{
    if (puzzle)
        return puzzle->Value;
    return -1;
}

bool QPuzzle::slideIfHasSpace()
{
    bool result = false;

    if (parentBoard)
    {
        result = parentBoard->trySlidePuzzle(*this);
    }

    return result;
}

void QPuzzle::applyPuzzleAnimation(SLIDE_DIRECTIONS dir)
{

    QPropertyAnimation *animation = createSlideAnimation(dir);
    QObject::connect(animation,SIGNAL(finished()),parentBoard,SLOT(on_animationFinished()));
    parentBoard->setAnimationStarted();
    animation->start();


}

QPropertyAnimation *QPuzzle::createSlideAnimation(SLIDE_DIRECTIONS dir)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    animation->setDuration(150);
    auto g = geometry();
    animation->setStartValue(g);

    auto size = width();

    switch(dir)
    {
        case UP:
        g.translate(0,-size);

        break;
        case DOWN:
        g.translate(0,size);

        break;
        case RIGHT:
        g.translate(size,0);

        break;
        case LEFT:
        g.translate(-size,0);

        break;
    }

    animation->setEndValue(g);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    return animation;
}

QPuzzle::~QPuzzle()
{
}

void QPuzzle::slotClicked()
{
    if (parentBoard->hasAnimationFinished())
        parentBoard->trySlidePuzzle(*this);

}


void QPuzzle::mousePressEvent(__attribute__((unused))QMouseEvent * event )
{
    emit clicked();
}


QLabelPuzzle::QLabelPuzzle(QWidget *parent):
    QPuzzle(parent)
{
}

QLabelPuzzle::~QLabelPuzzle()
{
}
