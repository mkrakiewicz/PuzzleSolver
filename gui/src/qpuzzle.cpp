#include "stdafx.h"

#include "qpuzzle.h"
#include "puzzle.h"
#include <QPropertyAnimation>

using namespace puzzle;

QPuzzle::QPuzzle(QWidget *parent) :
    QLabel(parent),
    puzzle(0)

{
    connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
}

void QPuzzle::setInnerPuzzle(std::shared_ptr<puzzle::IntPuzzle> puzzle)
{
    this->puzzle = puzzle;
}

const std::shared_ptr<IntPuzzle> QPuzzle::getInnerPuzzle()
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

void QPuzzle::slotClicked()
{

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(1000);
    auto g = geometry();
    animation->setStartValue(g);
    g.translate(0,150);

    animation->setEndValue(g);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    animation->start();

}




void QPuzzle::mousePressEvent(__attribute__((unused))QMouseEvent * event )
{
    emit clicked();
}


QLabelPuzzle::QLabelPuzzle(QWidget *parent):
    QPuzzle(parent)
{
}
