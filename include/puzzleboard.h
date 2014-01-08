#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H

#include <vector>
#include <sstream>
#include <memory>
#include <map>
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

    inline Dimension2D getDimensions() const
    {
        return *this;
    }
};

typedef std::map < Position2D, std::shared_ptr<Puzzle> > PointToPuzzleMap;

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
        setCorrectAligment();
    }

    std::shared_ptr<Puzzle> getPuzzle(const Position2D &pos)
    {
        return puzzles[pos];
    }

    virtual void setCorrectAligment() = 0;
    virtual std::shared_ptr<PuzzleBoard> clone() = 0;
    virtual BoardType getBoardType() = 0;
    virtual bool isEqual(PuzzleBoard &toCompare)
    {
        if (!(this->getDimensions() == toCompare.getDimensions()))
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
        for (u_int x=0; x<horizontalSize; x++)
        {
            for (u_int y=0; y<verticalSize; y++)
            {
                puzzles[Position2D(x,y)]->print();
            }
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

    inline PuzzleBoard& operator=(PuzzleBoard &a)
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
        Puzzle *p = new EmptyPuzzle;
        for (u_int x=0; x<horizontalSize; x++)
        {
            for (u_int y=0; y<verticalSize; y++)
            {
                puzzles[Position2D(x,y)] = std::shared_ptr<Puzzle>(p);
            }
        }
    };

    virtual std::shared_ptr<PuzzleBoard> clone()
    {
        return std::shared_ptr<PuzzleBoard>(new EmptyBoard(*this));
    };

    virtual BoardType getBoardType()
    {
        return BoardType::EMPTY;
    }

    virtual bool isEqual(PuzzleBoard &toCompare)
    {
        if (toCompare.getBoardType() != EMPTY)
            return false;
        return PuzzleBoard::isEqual(toCompare);
    };

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

    virtual bool isEqual(PuzzleBoard &toCompare)
    {
        if (toCompare.getBoardType() != ORDERED)
            return false;
        return PuzzleBoard::isEqual(toCompare);
    };

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
        for (u_int x=0; x<horizontalSize; x++)
        {
            for (u_int y=0; y<verticalSize; y++)
            {
                if ((x == (horizontalSize-1)) && (y == (verticalSize - 1)))
                    puzzles[Position2D(x,y)] = std::shared_ptr<Puzzle>(new EmptyPuzzle);
                else
                    puzzles[Position2D(x,y)] = std::shared_ptr<Puzzle>(new IntPuzzle(count++));
            }
        }
    }

    virtual std::shared_ptr<PuzzleBoard> clone()
    {
        return std::shared_ptr<PuzzleBoard>(new IntPuzzleBoard(*this));
    };

    virtual bool isEqual(PuzzleBoard &toCompare)
    {
        return OrderedBoard::isEqual(toCompare);
    }

    virtual ~IntPuzzleBoard(){}

};
}
#endif // PUZZLEBOARD_H
