#ifndef QPUZZLEBOARD_H
#define QPUZZLEBOARD_H

#include <memory>
#include <map>

namespace board {
    class Dimension2D;
    class IntPuzzleBoard;
}

class QLabelPuzzle;
class QWidget;
class Position2D;


typedef std::shared_ptr < std::map < u_int,std::shared_ptr <QLabelPuzzle> > > IDtoPuzzleObjPtr;
typedef std::shared_ptr < std::map < std::shared_ptr <QLabelPuzzle> , u_int> > PuzzleObjToIDPtr;
typedef std::shared_ptr < board::IntPuzzleBoard > IntPuzzleBoardPtr;


class QPuzzleBoard
{
public:
    QPuzzleBoard(const board::Dimension2D &dimensions);
    const std::shared_ptr <board::Dimension2D> dimensions;
    const board::Dimension2D & getDimensions();

    void setObjectForPuzzle(std::shared_ptr<QLabelPuzzle> puzzle);
    const std::shared_ptr<QLabelPuzzle> getPuzzle(u_int Value);
    const Position2D &getPosInBoard(const std::shared_ptr<QLabelPuzzle> puzzle);

//    const std::shared_ptr<QLabelPuzzle> getPuzzle(const Position2D &pos);


protected:
    IDtoPuzzleObjPtr  puzzleObjects;
    IntPuzzleBoardPtr innerBoard;
};


class QPuzzleBoardCreator
{
public:
    QPuzzleBoardCreator();
    void setParent(QWidget *parentForBoard);
    void setDimensions(const board::Dimension2D &dims);
    std::shared_ptr<QPuzzleBoard> createBoard();

protected:
    std::shared_ptr<board::Dimension2D> dimensions;
    QWidget *parentForBoard;
};



#endif // QPUZZLEBOARD_H
