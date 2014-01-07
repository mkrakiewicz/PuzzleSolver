#ifndef PUZZLEBOARDSMANAGER_H
#define PUZZLEBOARDSMANAGER_H

#include "puzzleboard.h"
#include <map>

typedef std::map<Position2D, std::shared_ptr<Position2D> > Position2DMap;
typedef std::map<NumericPuzzle, std::shared_ptr<NumericPuzzle> > NumericPuzzleMap;


template <class T>
class PuzzleBoardsManager : public Dimension2D
{
public:
    PuzzleBoardsManager(const Dimension2D &d) :
        Dimension2D(d)
    {
        fillPoints();
    }

    virtual PuzzleBoard<T> getEmptyBoard() = 0;
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
                        points[Position2D(x,y)] = shared_ptr<Position2D> (new Position2D(x,y));
                    }
            }
    }
};


class NumericPuzzleBoardsManager : public PuzzleBoardsManager<NumericPuzzle>
{
public:
    NumericPuzzleBoardsManager(const Dimension2D &d);

    virtual NumericPuzzleBoard getEmptyBoard();
protected:

};

#endif // PUZZLEBOARDSMANAGER_H
