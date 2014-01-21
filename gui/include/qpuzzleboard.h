#ifndef QPUZZLEBOARD_H
#define QPUZZLEBOARD_H

#include <memory>

namespace board {
    class Dimension2D;
}

class QPuzzleBoardCreator
{
public:
    void createBoard();

};


class QPuzzleBoard
{
public:
    QPuzzleBoard();


protected:
    std::shared_ptr < std::map<u_int,std::shared_ptr <QLabelPuzzle> > > puzzles;

};

#endif // QPUZZLEBOARD_H
