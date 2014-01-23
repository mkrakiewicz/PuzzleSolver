#ifndef QPUZZLEBOARD_H
#define QPUZZLEBOARD_H

#include <QObject>
#include <memory>
#include <map>
#include "enums.h"

namespace board {
    class Dimension2D;
    class IntPuzzleBoard;
}

class QLabelPuzzle;
class QWidget;
class Position2D;
class QPuzzle;


typedef std::shared_ptr < std::map < u_int,QLabelPuzzle* > > IDtoPuzzleObjPtr;
typedef std::shared_ptr < std::map < QLabelPuzzle* , u_int> > PuzzleObjToIDPtr;
typedef std::shared_ptr < board::IntPuzzleBoard > IntPuzzleBoardPtr;


class QPuzzleBoard : public QObject
{
    Q_OBJECT
public:
    QPuzzleBoard(QObject *parent, const board::Dimension2D &dimensions);
    const std::shared_ptr <board::Dimension2D> dimensions;
    const board::Dimension2D & getDimensions();

    void setObjectForPuzzle(QLabelPuzzle *puzzle);
    const QLabelPuzzle*  getPuzzle(u_int Value);
    const Position2D &getPosInBoard();
    bool trySlidePuzzle(QPuzzle &puzzle);

//    const std::shared_ptr<QLabelPuzzle> getPuzzle(const Position2D &pos);

    void setAnimationStarted();
    void setAnimationFinished();
    bool hasAnimationFinished();

protected:
    IDtoPuzzleObjPtr  puzzleObjects;
    IntPuzzleBoardPtr innerBoard;
    bool animationRunning;
public slots:

    void on_animationFinished();

};


class QPuzzleBoardCreator
{
public:
    QPuzzleBoardCreator();
    void setParent(QWidget *parentForBoard);
    void setDimensions(const board::Dimension2D &dims);
    QPuzzleBoard *createBoard();

protected:
    std::shared_ptr<board::Dimension2D> dimensions;
    QWidget *parentForBoard;
};



#endif // QPUZZLEBOARD_H
