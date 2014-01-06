#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H

#include <vector>
#include <sstream>
#include <memory>
#include <map>
#include "puzzle.h"
#include "exceptions.h"
#include "position2d.h"

class Dimension2D
{
public:
    Dimension2D(int sizeX, int sizeY);
    virtual ~Dimension2D(){}

    const unsigned int horizontalSize, verticalSize;
};

template <class SourceObj,class DestObj>
class PointerToPointerMapper
{
public:
    PointerToPointerMapper()
    {

    }

    void mapPointerToPointer(std::shared_ptr<SourceObj> source, std::shared_ptr<DestObj> dest)
    {
        mappedPointers[source] = dest;
    }

    std::shared_ptr<DestObj>  getPointerFromPointer(std::shared_ptr<SourceObj> source)
    {
        return mappedPointers[source];
    }

    virtual ~PointerToPointerMapper(){}

private:
    std::map < std::shared_ptr<SourceObj>, std::shared_ptr<DestObj> > mappedPointers;
};

typedef PointerToPointerMapper<Position2D,Puzzle> PositionToPuzzleMapper;

template <class T>
class PuzzleBoard : public Dimension2D
{
public:
    PuzzleBoard(const Dimension2D &d):
        Dimension2D(d)
    {

    }

    virtual ~PuzzleBoard(){}

};

typedef PuzzleBoard<int> NumericPuzzleBoard;

//template <class T>
//class PuzzleBoardState : public PointStateContainer<T>
//{
//public:
//    PuzzleBoardState(const Dimension2D &d):
//        PointStateContainer<T>(d)
//    {

//    }

//    T getPuzzleAt

//    virtual ~PuzzleBoardState(){}
//};

//typedef  PuzzleBoardState<int> NumericPuzzleBoardState;

#endif // PUZZLEBOARD_H
