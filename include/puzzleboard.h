#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H


#include <sstream>
#include <vector>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include "puzzle.h"
#include "exceptions.h"
#include "position2d.h"
#include "enums.h"

using namespace puzzle;
namespace board {

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
    PuzzlePositionContainer():
        emptyPuzzlePos(0),
        puzzles(0),
        points(0)
    {}
    void insertPuzzle(Puzzle &puzzle, Position2D& point)
    {
        if (findPuzzle(point).get() == 0)
        {   auto _puzzle = puzzle.clone();
            auto _point = point.clone();
            puzzles.push_back(_puzzle);
            points.push_back(_point);
        } else
        {
            std::replace(puzzles.begin()+counter,puzzles.begin()+counter+1,puzzles.at(counter), puzzle.clone());
        }
        if (puzzle.getType() == EMPTY)
        {
            EmptyPuzzle p;
            emptyPuzzlePos = findPoint(p);
        }

    }

    std::shared_ptr<puzzle::Puzzle> findPuzzle(const Position2D &point)
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

        return std::shared_ptr<puzzle::Puzzle>(0);
    }

    std::shared_ptr<Position2D> findPoint(puzzle::Puzzle &puzzle)
    {
        int i;
        bool found = false;

        for (i=0; i<puzzles.size(); i++)
        {
            if (*puzzles[i] == puzzle)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            counter = i;
            return points[i];
        }

        return std::shared_ptr<Position2D>(0);
    }

    std::shared_ptr<Position2D> getEmptyPuzzlePos()
    {
        return emptyPuzzlePos;
    }

    void swap(Position2D &pos1,Position2D &pos2)
    {
        std::shared_ptr<puzzle::Puzzle> puz1 = findPuzzle(pos1);
        std::shared_ptr<puzzle::Puzzle> puz2 = findPuzzle(pos2);
        insertPuzzle(*puz2,pos1);
        insertPuzzle(*puz1,pos2);
    }


protected:
    std::vector< std::shared_ptr<puzzle::Puzzle> > puzzles;
    std::vector< std::shared_ptr<Position2D> > points;
    std::shared_ptr<Position2D> emptyPuzzlePos;
private:
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
        puzzle::EmptyPuzzle p;
        fillWith(p);
    }

    void setPuzzle(Position2D pos, puzzle::Puzzle &puz)
    {
        puzzles.insertPuzzle(puz,pos);
    }

    std::shared_ptr<puzzle::Puzzle> getPuzzle(Position2D &pos)
    {
        return puzzles.findPuzzle(pos);
    }

    void fillWith(puzzle::Puzzle &puzzle){
        {
            for (u_int x=0; x<horizontalSize; x++)
            {
                for (u_int y=0; y<verticalSize; y++)
                {
                    Position2D pos(x,y);
                    puzzles.insertPuzzle(puzzle,pos);
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

    std::string toString()
    {
        std::stringstream s;
        for (u_int y=0; y<verticalSize; y++)
        {
            for (u_int x=0; x<horizontalSize; x++)
            {
                Position2D pos(x,y);
                s << puzzles.findPuzzle(pos)->toString();
            }
            s << std::endl;
        }
        return s.str();
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

    inline bool isValidPos(Position2D &pos)
    {
        if (pos.X < 0)
            return false;
        if (pos.Y < 0)
            return false;
        if (pos.X >= horizontalSize)
            return false;
        if (pos.Y >= verticalSize)
            return false;
        return true;
    }

    SLIDE_DIRECTIONS slideDirToEmptyMovement(const SLIDE_DIRECTIONS &dir)
    {
        switch(dir)
        {
            case UP:
                return DOWN;
            case DOWN:
                return UP;
            case LEFT:
                return RIGHT;
            case RIGHT:
                return LEFT;

            default:
                    throw Exception("Forgot to implement new direction slidePuzzle");
        }
    }

    Position2D determineEmptyPosAfterSlide(const SLIDE_DIRECTIONS &dir)
    {
        Position2D emptyPos = *puzzles.getEmptyPuzzlePos();

        switch(slideDirToEmptyMovement(dir))
        {
            case UP:
                return Position2D(emptyPos.X, emptyPos.Y-1);
            case DOWN:
                return Position2D(emptyPos.X, emptyPos.Y+1);
            case LEFT:
                return Position2D(emptyPos.X-1, emptyPos.Y);
            case RIGHT:
                return Position2D(emptyPos.X+1, emptyPos.Y);

                default:
            throw Exception("Forgot to implement new direction for determineNewSlidePos");
        }
    }


    bool slidePuzzle(const SLIDE_DIRECTIONS &dir)
    {
        std::shared_ptr<Position2D> emptyPos = puzzles.getEmptyPuzzlePos();
        Position2D newPos = determineEmptyPosAfterSlide(dir);

        if (!isValidPos(newPos))
            return false;

        puzzles.swap(*emptyPos,newPos);
        return true;

    }

    std::shared_ptr<Position2D> getEmptyPuzzlePos()
    {
        std::shared_ptr<Position2D> p(new Position2D(*puzzles.getEmptyPuzzlePos()));
        return p;
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
       puzzle::EmptyPuzzle p;
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
        setCorrectAligment();
    }

    void setCorrectAligment()
    {
        uint count = 1;
        for (u_int y=0; y<verticalSize; y++)
        {
            for (u_int x=0; x<horizontalSize; x++)
            {
                Position2D pos(x,y);
                if ((x == (horizontalSize-1)) && (y == (verticalSize - 1)))
                {
                    EmptyPuzzle p;
                    puzzles.insertPuzzle(p,pos);
                }
                else
                {
                    puzzle::IntPuzzle p(count++);
                    puzzles.insertPuzzle(p, pos);
                }
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
