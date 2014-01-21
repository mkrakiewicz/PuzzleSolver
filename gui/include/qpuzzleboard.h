#ifndef QPUZZLEBOARD_H
#define QPUZZLEBOARD_H

#include <memory>
#include <map>

namespace board {
    class Dimension2D;
}

class QLabelPuzzle;
class QWidget;


class QPuzzleBoard
{
public:
    QPuzzleBoard(const board::Dimension2D &dimensions);
    const std::shared_ptr <board::Dimension2D> dimensions;
    const board::Dimension2D & getDimensions();
protected:
    std::shared_ptr < std::map < u_int,std::shared_ptr <QLabelPuzzle> > >  puzzles;

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
