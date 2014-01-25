#ifndef QSOLUTIONANIMATOR_H
#define QSOLUTIONANIMATOR_H

#include "QObject"
#include <vector>
#include "enums.h"

class QPropertyAnimation;
class QPuzzleBoard;

class QSolutionAnimator : public QObject
{
    Q_OBJECT
public:
    QSolutionAnimator(QObject *parent = 0);
    void setBoardToAnimate(QPuzzleBoard*board);
    void setSteps(std::vector<board::SLIDE_DIRECTIONS> steps);
    void setAnimations(std::vector<QPropertyAnimation*> animations);
    void reset();
    void start();
public slots:

    void on_animateNext();
protected:
    void animateNext();
    std::vector<board::SLIDE_DIRECTIONS> steps;
    std::vector<QPropertyAnimation*> animations;
    QPuzzleBoard* board;
    u_int current;
    bool animated;
};

#endif // QSOLUTIONANIMATOR_H
