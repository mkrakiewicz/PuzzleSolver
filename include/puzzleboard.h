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

typedef PointerToPointerMapper<Position2D,NumericPuzzle> PositionToNumericPuzzleMapper;


template <class T>
class PuzzleBoardContainer : public Dimension2D
{
public:
    PuzzleBoardContainer(const Dimension2D &d):
        Dimension2D(d)
    {

    }

    void setPuzzle(std::shared_ptr<Position2D> pos, std::shared_ptr<T> puzzle)
    {
        this->puzzles.mapPointerToPointer(pos,puzzle);
    }

    std::shared_ptr<T> getPuzzle(std::shared_ptr<Position2D> pos)
    {
        return puzzles.getPointerFromPointer(pos);
    }

//    void setPuzzlesTo(T value){
//           for (int y=0; y<this->verticalSize; y++)
//           {
//               for (int x=0; x<this->horizontalSize; x++)
//               {
//                   this->setPuzzle(std::shared_ptr<Position2D>(new Position2D(x,y)),std::shared_ptr<T>(new T(x,y)));
//                   PointState<T> p(x,y,value);
//                   setState(p);
//               }
//           }
//       }

    virtual ~PuzzleBoardContainer(){}

protected:
    PointerToPointerMapper<Position2D,T> puzzles;
};


typedef PuzzleBoardContainer<int> NumericPuzzleBoardContainer;


template <class T>
class PuzzleBoard : public Dimension2D
{
public:
     PuzzleBoard(const Dimension2D &d, const PuzzleBoardContainer<T> &container):
         Dimension2D(d), puzzleContainer(container)
     {

     }

     std::shared_ptr<T> getPuzzle(std::shared_ptr<Position2D> pos)
     {
         return puzzleContainer.getPuzzle(pos);
     }

     virtual ~PuzzleBoard(){}

protected:
     PuzzleBoardContainer<T> puzzleContainer;
};

typedef  PuzzleBoard<int> NumericPuzzleBoard;

#endif // PUZZLEBOARD_H
