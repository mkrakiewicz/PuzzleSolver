#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H


#include <vector>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include "enums.h"


#ifdef MY_DEBUG
#include <QDebug>
#include "dbg.h"
#endif

namespace puzzle {
    class Puzzle;
    class IntPuzzle;
}


class Position2D;

namespace board {

class EmptyBoard;
class IntPuzzleBoard;

class Dimension2D
{
public:
    Dimension2D();
    Dimension2D(int sizeX, int sizeY);
    virtual ~Dimension2D(){}

    bool operator==(const Dimension2D &toCompare) const;
    bool operator!=(const Dimension2D &toCompare) const;
    bool operator <(const Dimension2D &toCompare) const;


    Dimension2D getDimensions() const;
    u_int getMultipliedDimensions();

    unsigned int horizontalSize, verticalSize;
};

class PuzzlePointerPool
{
public:
    Position2D* getPointerForObject(Position2D &pos);
    puzzle::Puzzle* getPointerForObject(const puzzle::Puzzle &puzzle);

    virtual ~PuzzlePointerPool();
protected:
    Position2D* createNew(Position2D &pos);
    puzzle::Puzzle* createNew(const puzzle::Puzzle &puzzle);

    std::vector< std::shared_ptr<puzzle::Puzzle> > puzzles;
    std::vector< std::shared_ptr<Position2D> > points;
};

class PuzzlePositionContainer
{
public:
    PuzzlePositionContainer();

    void insertPuzzle(puzzle::Puzzle&puzzle, Position2D& point);
    puzzle::Puzzle* findPuzzle(Position2D &point) ;
    puzzle::Puzzle* findPuzzle(const puzzle::Puzzle &puzzle);
    Position2D* findPoint(puzzle::Puzzle &puzzle);
    Position2D* getEmptyPuzzlePos();
    void swap(Position2D &pos1,Position2D &pos2);

    virtual ~PuzzlePositionContainer();

protected:
    static PuzzlePointerPool pool;

    std::map< Position2D*, puzzle::Puzzle* > positionToPuzzle;
    std::map< puzzle::Puzzle*, Position2D* > puzzleToPosition;


    Position2D* emptyPuzzlePos;
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
    PuzzleBoard(const Dimension2D &d);

#ifdef MY_DEBUG
    static AVG avg;
#endif

    void setPuzzle(Position2D pos, puzzle::Puzzle &puz);
    puzzle::Puzzle *getPuzzle(Position2D &pos) ;
    puzzle::Puzzle *getPuzzle(const puzzle::Puzzle &puzzle);
    Position2D *getPuzzlePos(puzzle::Puzzle &puzzle);


    void fillWith(puzzle::Puzzle &puzzle);
    virtual void setCorrectAlignment()  = 0;
    virtual std::shared_ptr<PuzzleBoard> clone() const = 0;

    std::shared_ptr<PuzzleBoard> getBoardWithCorrectAlignment();


    u_int getNumberOfPuzzlesInWrongPosition();
    u_int getSumOfDistances();

    virtual BoardType getBoardType() = 0;
    bool isEqual(PuzzleBoard &toCompare);

    std::string toString();

    inline bool operator==(PuzzleBoard &toCompare)
    {
        return this->isEqual(toCompare);
    }

    inline virtual bool operator!=(PuzzleBoard &toCompare)
    {
        return !this->isEqual(toCompare);
    }

    inline  virtual PuzzleBoard& operator=(const PuzzleBoard &)
    {
        return *this->clone();
    }

    bool isValidPos(Position2D &pos);


    board::SLIDE_DIRECTIONS emptyPuzzleSlideDirection(const board::SLIDE_DIRECTIONS &puzzleSlideDirection);
    std::shared_ptr<Position2D> determineEmptyPosAfterSlide(const board::SLIDE_DIRECTIONS &dir);
    bool slidePuzzle(const board::SLIDE_DIRECTIONS &dir);
    std::shared_ptr<Position2D> getEmptyPuzzlePos();
    std::shared_ptr<board::SLIDE_DIRECTIONS> getSlideDir(puzzle::Puzzle &puz);

    static std::vector<board::SLIDE_DIRECTIONS> directions;


    virtual ~PuzzleBoard(){}

    int calculateHammingPriority(const int &movesMadeSoFar);
    int calculateManhattanPriority(const int &movesMadeSoFar);
protected:
    virtual std::shared_ptr<PuzzleBoard> getBoardToCompare() = 0;

    PointToPuzzleMap puzzles;
};

typedef std::shared_ptr< std::map <Dimension2D,std::shared_ptr<EmptyBoard> > >
Dimension2DToEmptyBoardMapPtr;

class EmptyBoard : public PuzzleBoard
{
public:

    EmptyBoard(const Dimension2D &d);
    virtual void setCorrectAlignment();
    virtual std::shared_ptr<PuzzleBoard> clone() const;
    virtual BoardType getBoardType();


    virtual ~EmptyBoard();
protected:
     static Dimension2DToEmptyBoardMapPtr correctlyAlignedBoards;
     virtual std::shared_ptr<PuzzleBoard> getBoardToCompare();
};

class OrderedBoard : public PuzzleBoard
{
public:
    OrderedBoard(const Dimension2D &d);

    virtual BoardType getBoardType();

    virtual ~OrderedBoard();
};

typedef std::shared_ptr< std::map <Dimension2D,std::shared_ptr<IntPuzzleBoard> > >
Dimension2DToIntPuzzleBoardMapPtr;

class IntPuzzleBoard : public OrderedBoard
{
public:
    IntPuzzleBoard(const Dimension2D &d);


    void setCorrectAlignment();
    virtual std::shared_ptr<PuzzleBoard> clone() const;


    virtual ~IntPuzzleBoard();
protected:
     static Dimension2DToIntPuzzleBoardMapPtr correctlyAlignedBoards;
     virtual std::shared_ptr<PuzzleBoard> getBoardToCompare();
};
}
#endif // PUZZLEBOARD_H
