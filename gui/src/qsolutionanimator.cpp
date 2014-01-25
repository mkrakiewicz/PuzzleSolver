#include "qsolutionanimator.h"
#include <QPropertyAnimation>
#include <qpuzzleboard.h>
#include "qpuzzle.h"
#include "exceptions.h"

QSolutionAnimator::QSolutionAnimator(QObject *parent):
    QObject(parent),
    animations(0),
    board(0),
    current(0),
    animated(false)
{
}

void QSolutionAnimator::setBoardToAnimate(QPuzzleBoard *board)
{
    this->board = board;
}

void QSolutionAnimator::setSteps(std::vector<board::SLIDE_DIRECTIONS> steps)
{
    this->steps = steps;
}

void QSolutionAnimator::setAnimations(std::vector<QPropertyAnimation *> animations)
{
    this->animations = animations;
}

void QSolutionAnimator::reset()
{
    animated = false;
    steps.clear();
    animations.clear();
    current = 0;
}

void QSolutionAnimator::start()
{
    if (board !=0 && !animated){
        animated = true;
        animateNext();
    }
}

void QSolutionAnimator::animateNext()
{
     if (board == 0)
         return;

    if (steps.size() > current)
    {
        auto dir = steps[current];
        auto p = board->getSlidablePuzzle(dir);
        if (p != 0) {
            if (!board->slideInnerPuzzle(dir))
                throw Exception("Couldn't slide with had solution!");
            auto a = p->createSlideAnimation(dir);
            QObject::connect(a,SIGNAL(finished()),this,SLOT(on_animateNext()));
            a->start();
            current++;
        }
    }
}


void QSolutionAnimator::on_animateNext()
{
    animateNext();
}
