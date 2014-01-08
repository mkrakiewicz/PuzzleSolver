#ifndef PUZZLEBOARDSMANAGER_H
#define PUZZLEBOARDSMANAGER_H

#include "puzzleboard.h"
#include <map>
#include <memory>

/*typedef std::map<Position2D, std::shared_ptr<Position2D> > Position2DMap;
typedef std::map<IntPuzzle, std::shared_ptr<IntPuzzle> > NumericPuzzleMap;


template <class T>
class PuzzleBoardsManager : public Dimension2D
{
public:
    PuzzleBoardsManager(const Dimension2D &d) :
        Dimension2D(d)
    {
        fillPoints();
    }

    virtual PuzzleBoard getEmptyBoard() = 0;
    virtual ~PuzzleBoardsManager(){}
protected:
    Position2DMap points;
    std::map<T, std::shared_ptr<T> > puzzles;

    void fillPoints()
    {
            for (u_int x = 0; x<horizontalSize; x++ )
            {
                    for (u_int y = 0; y<verticalSize; y++ )
                    {
                        points[Position2D(x,y)] = std::shared_ptr<Position2D> (new Position2D(x,y));
                    }
            }
    }
};


class NumericPuzzleBoardsManager : public PuzzleBoardsManager<IntPuzzle>
{
public:
    NumericPuzzleBoardsManager(const Dimension2D &d);

    virtual NumericPuzzleBoard getEmptyBoard();
protected:

};*/

#endif // PUZZLEBOARDSMANAGER_H
