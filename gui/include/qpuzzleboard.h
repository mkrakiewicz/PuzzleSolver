#ifndef QPUZZLEBOARD_H
#define QPUZZLEBOARD_H

#include <QWidget>
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
class PuzzleSolver;

typedef std::shared_ptr < std::map < u_int,QLabelPuzzle* > > IDtoPuzzleObjPtr;
typedef std::shared_ptr < std::map < QLabelPuzzle* , u_int> > PuzzleObjToIDPtr;
typedef std::shared_ptr < board::IntPuzzleBoard > IntPuzzleBoardPtr;


class QPuzzleBoard : public QWidget
{
    Q_OBJECT
public:
    QPuzzleBoard(QWidget *parent, const board::Dimension2D &dimensions);
    const std::shared_ptr <board::Dimension2D> dimensions;
    const board::Dimension2D & getDimensions();

    void setObjectForPuzzle(QLabelPuzzle *puzzle);
    QLabelPuzzle *getPuzzle(u_int Value);
    const Position2D &getPosInBoard();
    bool trySlidePuzzle(QPuzzle &puzzle);
//    bool trySlidePuzzle(board::SLIDE_DIRECTIONS direction);
    QLabelPuzzle *getSlidablePuzzle(const board::SLIDE_DIRECTIONS &direction);

    bool slideInnerPuzzle(board::SLIDE_DIRECTIONS direction);


    void setAnimationStarted();
    void setAnimationFinished();
    bool hasAnimationFinished();

    void deleteInnerObjects();
    bool solveBoard() throw();
    IntPuzzleBoardPtr getInnerBoard();

    virtual ~QPuzzleBoard();
    std::shared_ptr<PuzzleSolver> solver;

//    Position2D directionToPosition(const Position2D &initialPos, const board::SLIDE_DIRECTIONS &direction);
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

     virtual ~QPuzzleBoardCreator();
protected:
    std::shared_ptr<board::Dimension2D> dimensions;
    QWidget *parentForBoard;
};



#endif // QPUZZLEBOARD_H
