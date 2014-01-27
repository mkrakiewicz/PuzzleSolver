#include "qsolutionanimator.h"
#include <QPropertyAnimation>
#include <qpuzzleboard.h>
#include "qpuzzle.h"
#include "exceptions.h"

QSlideAnimator::QSlideAnimator(QObject *parent):
    QObject(parent),
    animations(0),
    board(0),
    current(0),
    animated(false)
{
}

void QSlideAnimator::setBoardToAnimate(QPuzzleBoard *board)
{
    this->board = board;
}

void QSlideAnimator::setSteps(std::vector<board::SLIDE_DIRECTIONS> steps)
{
    this->steps = steps;
}

void QSlideAnimator::setAnimations(std::vector<QPropertyAnimation *> animations)
{
    this->animations = animations;
}

void QSlideAnimator::reset()
{
    animated = false;
    steps.clear();
    animations.clear();
    current = 0;
}

void QSlideAnimator::start()
{
    if (board !=0 && !animated){
        animated = true;
        animateNext();
    }
}

void QSlideAnimator::animateNext()
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


void QSlideAnimator::on_animateNext()
{
    animateNext();
}
