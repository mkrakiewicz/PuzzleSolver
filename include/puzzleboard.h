#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H

#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include "puzzle.h"
#include "exceptions.h"
#include "position2d.h"

namespace boards {

class Dimension2D
{
public:
    Dimension2D(int sizeX, int sizeY);
    virtual ~Dimension2D(){}

    const unsigned int horizontalSize, verticalSize;

    inline bool operator==(const Dimension2D &toCompare) const
    {
        if (horizontalSize != toCompare.horizontalSize)
            return false;
        if (verticalSize != toCompare.verticalSize)
            return false;
        return true;
    }

    inline bool operator!=(const Dimension2D &toCompare) const
    {
        return !operator==(toCompare);
    }

    inline Dimension2D getDimensions() const
    {
        return *this;
    }
};

class PuzzlePositionContainer
{
public:
    void insertPuzzle(std::shared_ptr<Puzzle> puzzle, std::shared_ptr<Position2D> point)
    {

        if (findPuzzle(*point).get() == 0)
        {
            puzzles.push_back(puzzle);
            points.push_back(point);
        } else
        {
            std::replace(puzzles.begin()+counter,puzzles.begin()+counter+1,puzzles.at(counter), puzzle);
        }

    }

    std::shared_ptr<Puzzle> findPuzzle(Position2D &point)
    {
        int i;
        bool found = false;

        for (i=0; i<points.size(); i++)
        {
            if (*points[i] == point)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            counter = i;
            return puzzles[i];
        }

        return std::shared_ptr<Puzzle>(0);
    }

protected:
    std::vector< std::shared_ptr<Puzzle> > puzzles;
    std::vector< std::shared_ptr<Position2D> > points;
    int counter;

};

typedef PuzzlePositionContainer PointToPuzzleMap;

enum BoardType
{
    EMPTY,
    ORDERED
};

class PuzzleBoard : public Dimension2D
{
public:
    PuzzleBoard(const Dimension2D &d):
        Dimension2D(d)
    {
        EmptyPuzzle p;
        fillWith(p);
    }

    void setPuzzle(Position2D pos, const Puzzle &puz)
    {
        puzzles.insertPuzzle(puz.clone(),pos.clone());
    }

    std::shared_ptr<Puzzle> getPuzzle(Position2D &pos)
    {
        return puzzles.findPuzzle(pos);
    }

    void fillWith(Puzzle &puzzle){
        {
            std::shared_ptr<Puzzle> p = puzzle.clone();
            for (u_int x=0; x<horizontalSize; x++)
            {
                for (u_int y=0; y<verticalSize; y++)
                {
                    Position2D pos(x,y);
                    puzzles.insertPuzzle(p,pos.clone());
                    puzzles.findPuzzle(pos)->getType();
                }
            }
        }

    }

    virtual void setCorrectAligment()  = 0;
    virtual std::shared_ptr<PuzzleBoard> clone() = 0;
    virtual BoardType getBoardType() = 0;

    bool isEqual(PuzzleBoard &toCompare)
    {
        if (this->getDimensions() != toCompare.getDimensions())
            return false;

        if (toCompare.getBoardType() != getBoardType())
            return false;

        for (u_int x=0; x<horizontalSize; x++)
        {
            for (u_int y=0; y<verticalSize; y++)
            {
                Position2D c(x,y);
                if (*(getPuzzle(c)) !=  *(toCompare.getPuzzle(c)))
                    return false;
            }
        }
        return true;
    }

    void print()
    {
        for (u_int y=0; y<verticalSize; y++)
        {
            for (u_int x=0; x<horizontalSize; x++)
            {
                Position2D pos(x,y);
                puzzles.findPuzzle(pos)->print();
            }
            std::cout << std::endl;
        }
    }

    inline bool operator==(PuzzleBoard &toCompare)
    {
        return this->isEqual(toCompare);
    }

    inline virtual bool operator!=(PuzzleBoard &toCompare)
    {
        return !this->isEqual(toCompare);
    }

    inline  virtual PuzzleBoard& operator=(PuzzleBoard &a)
    {
        return *this->clone();
    }

    virtual ~PuzzleBoard(){}

protected:
    PointToPuzzleMap puzzles;
};

class EmptyBoard : public PuzzleBoard
{
public:

    EmptyBoard(const Dimension2D &d):
        PuzzleBoard(d)
    {

    }

    virtual void setCorrectAligment()
    {
       EmptyPuzzle p;
       fillWith(p);
    }

    virtual std::shared_ptr<PuzzleBoard> clone()
    {
        return std::shared_ptr<PuzzleBoard>(new EmptyBoard(*this));
    }

    virtual BoardType getBoardType()
    {
        return BoardType::EMPTY;
    }

    virtual ~EmptyBoard() {}
};

class OrderedBoard : public PuzzleBoard
{
public:
    OrderedBoard(const Dimension2D &d):
        PuzzleBoard(d)
    {
    }
    virtual BoardType getBoardType()
    {
        return BoardType::ORDERED;
    }

    virtual ~OrderedBoard() {}
};

class IntPuzzleBoard : public OrderedBoard
{
public:
    IntPuzzleBoard(const Dimension2D &d):
        OrderedBoard(d)
    {
    }

    void setCorrectAligment()
    {
        uint count = 1;
        for (u_int y=0; y<verticalSize; y++)
        {
            for (u_int x=0; x<horizontalSize; x++)
            {
                if ((x == (horizontalSize-1)) && (y == (verticalSize - 1)))
                    puzzles.insertPuzzle(std::shared_ptr<Puzzle>(new EmptyPuzzle),std::shared_ptr<Position2D>(new Position2D(x,y)));
                else
                    puzzles.insertPuzzle(std::shared_ptr<Puzzle>(new IntPuzzle(count++)),std::shared_ptr<Position2D>(new Position2D(x,y)));
            }
        }
    }

    virtual std::shared_ptr<PuzzleBoard> clone()
    {
        return std::shared_ptr<PuzzleBoard>(new IntPuzzleBoard(*this));
    }

    virtual ~IntPuzzleBoard(){}

};
}
#endif // PUZZLEBOARD_H
