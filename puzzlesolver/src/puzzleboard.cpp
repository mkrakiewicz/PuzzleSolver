#include "stdafx.h"

#include "puzzleboard.h"
#include <sstream>
#include <map>
#include "puzzle.h"
#include "exceptions.h"
#include "position2d.h"
#include "enums.h"


using namespace puzzle;
using namespace std;


namespace board {

std::vector<board::SLIDE_DIRECTIONS> PuzzleBoard::directions = {UP,DOWN,LEFT,RIGHT};


PuzzlePointerPool PuzzlePositionContainer::pool;

Dimension2DToEmptyBoardMapPtr EmptyBoard::correctlyAlignedBoards(0);
Dimension2DToIntPuzzleBoardMapPtr IntPuzzleBoard::correctlyAlignedBoards(0);



Dimension2D::Dimension2D():
    horizontalSize(0),
    verticalSize(0)
{
}

Dimension2D::Dimension2D(int horizontalSize, int verticalSize):
    horizontalSize(horizontalSize), verticalSize(verticalSize)
{
}

bool Dimension2D::operator ==(const Dimension2D &toCompare) const
{
    if (horizontalSize != toCompare.horizontalSize)
        return false;
    if (verticalSize != toCompare.verticalSize)
        return false;
    return true;
}

bool Dimension2D::operator !=(const Dimension2D &toCompare) const
{
    return !operator==(toCompare);
}

bool Dimension2D::operator <(const Dimension2D &toCompare) const
{
    if ((verticalSize < toCompare.verticalSize) && (horizontalSize < toCompare.horizontalSize))
        return true;

    int thisSum = verticalSize+horizontalSize , otherSum = toCompare.horizontalSize+toCompare.verticalSize;

    if (thisSum < otherSum)
        return true;

    return false;
}

Dimension2D Dimension2D::getDimensions() const
{
    return *this;
}

u_int Dimension2D::getMultipliedDimensions()
{
    return verticalSize * horizontalSize;
}

PuzzlePositionContainer::PuzzlePositionContainer() :
    emptyPuzzlePos(0)

{}

void PuzzlePositionContainer::insertPuzzle(Puzzle &puzzle, Position2D &point)
{
    auto _puzzle = pool.getPointerForObject(puzzle);
    auto _point =  pool.getPointerForObject(point);
    puzzleToPosition[_puzzle] = _point;
    positionToPuzzle[_point] = _puzzle;

    if (puzzle.getType() == puzzle::EMPTY)
    {
        EmptyPuzzle p;
        emptyPuzzlePos = findPoint(p);
    }

}

std::shared_ptr<Puzzle> PuzzlePositionContainer::findPuzzle(const Position2D &point)
{
    std::shared_ptr<Position2D> pos = pool.getPointerForObject(point);
    auto result = positionToPuzzle.find(pos);
    if ( result == positionToPuzzle.end() ) {
        throw Exception("Position not found? object should have been created!");
    }
    return result->second;

}

std::shared_ptr<Puzzle> PuzzlePositionContainer::findPuzzle(u_int val)
{
    IntPuzzle a(val);
    std::shared_ptr<Puzzle> puz = pool.getPointerForObject(a);
    return puz;

}

std::shared_ptr<Position2D> PuzzlePositionContainer::findPoint(Puzzle &puzzle)
{
    auto result = puzzleToPosition.find(pool.getPointerForObject(puzzle));
    if ( result == puzzleToPosition.end() ) {
        return std::shared_ptr<Position2D>(0);
    } else return result->second;
}

std::shared_ptr<Position2D> PuzzlePositionContainer::getEmptyPuzzlePos()
{
    return emptyPuzzlePos;
}

void PuzzlePositionContainer::swap(Position2D &pos1, Position2D &pos2)
{
    std::shared_ptr<puzzle::Puzzle> puz1 = findPuzzle(pos1);
    std::shared_ptr<puzzle::Puzzle> puz2 = findPuzzle(pos2);
    if ((puz1 == 0) || (puz2 == 0))
        return;

    insertPuzzle(*puz2,pos1);
    insertPuzzle(*puz1,pos2);
}

PuzzlePositionContainer::~PuzzlePositionContainer()
{
}

PuzzleBoard::PuzzleBoard(const Dimension2D &d):
    Dimension2D(d)
{
    puzzle::EmptyPuzzle p;
    fillWith(p);
}

void PuzzleBoard::setPuzzle(Position2D pos, Puzzle &puz)
{
    puzzles.insertPuzzle(puz,pos);
}

std::shared_ptr<Puzzle> PuzzleBoard::getPuzzle(Position2D &pos)
{
    auto p = puzzles.findPuzzle(pos);
    if (p == 0) {
        stringstream s;
        s << "Puzzle Not found? Requested position:";
        s << pos.toString() << endl;
        throw Exception(s.str());
    }
    return p->clone();
}

std::shared_ptr<Puzzle> PuzzleBoard::getPuzzle(u_int value)
{
    return puzzles.findPuzzle(value);
}


void PuzzleBoard::fillWith(Puzzle &puzzle)
{

    for (u_int x=0; x<horizontalSize; x++)
    {
        for (u_int y=0; y<verticalSize; y++)
        {
            Position2D pos(x,y);
            puzzles.insertPuzzle(puzzle,pos);
        }
    }


}

std::shared_ptr<PuzzleBoard> PuzzleBoard::getBoardWithCorrectAlignment()
{
    return getBoardToCompare();
}

u_int PuzzleBoard::getNumberOfPuzzlesInWrongPosition()
{
    u_int wrong = 0;
    EmptyPuzzle e;
    auto reference = getBoardWithCorrectAlignment();
    for (u_int x=0; x<horizontalSize; x++)
    {
        for (u_int y=0; y<verticalSize; y++)
        {
            Position2D pos(x,y);
            auto p1 = getPuzzle(pos);
            if (*p1 == e)
                continue;
            auto p2 = reference->getPuzzle(pos);
            if ((*p1) != (*p2))
                wrong++;
        }
    }
    return wrong;
}

bool PuzzleBoard::isEqual(PuzzleBoard &toCompare)
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

std::string PuzzleBoard::toString()
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

bool PuzzleBoard::isValidPos(Position2D &pos)
{
    if (pos.X < 0)
        return false;
    if (pos.Y < 0)
        return false;
    if (pos.X >= (int)horizontalSize)
        return false;
    if (pos.Y >= (int)verticalSize)
        return false;
    return true;
}

SLIDE_DIRECTIONS PuzzleBoard::emptyPuzzleSlideDirection(const SLIDE_DIRECTIONS &puzzleSlideDirection)
{
    switch(puzzleSlideDirection)
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

Position2D PuzzleBoard::determineEmptyPosAfterSlide(const SLIDE_DIRECTIONS &dir)
{
    Position2D emptyPos = *puzzles.getEmptyPuzzlePos();

    switch(emptyPuzzleSlideDirection(dir))
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

bool PuzzleBoard::slidePuzzle(const SLIDE_DIRECTIONS &dir)
{
    std::shared_ptr<Position2D> emptyPos = puzzles.getEmptyPuzzlePos();
    Position2D newPos = determineEmptyPosAfterSlide(dir);

    if (!isValidPos(newPos))
        return false;

    puzzles.swap(*emptyPos,newPos);
    return true;

}

std::shared_ptr<Position2D> PuzzleBoard::getEmptyPuzzlePos()
{
    std::shared_ptr<Position2D> p(new Position2D(*puzzles.getEmptyPuzzlePos()));
    return p;
}

std::shared_ptr<board::SLIDE_DIRECTIONS> PuzzleBoard::getSlideDir(Puzzle &puz)
{
    std::shared_ptr<board::SLIDE_DIRECTIONS>  result(0);

    auto pos = puzzles.findPoint(puz);
    auto empty = puzzles.getEmptyPuzzlePos();
    Position2D p1 = Position2D(pos->X, pos->Y-1);
    Position2D p2 = Position2D(pos->X, pos->Y+1);
    Position2D p3 = Position2D(pos->X-1, pos->Y);
    Position2D p4 = Position2D(pos->X+1, pos->Y);

     if ((*empty) == p1)
            return result = std::shared_ptr<board::SLIDE_DIRECTIONS> (new SLIDE_DIRECTIONS(UP));
     if ((*empty) == p2)
            return result = std::shared_ptr<board::SLIDE_DIRECTIONS> (new SLIDE_DIRECTIONS(DOWN));
     if ((*empty) == p3)
        return result = std::shared_ptr<board::SLIDE_DIRECTIONS> (new SLIDE_DIRECTIONS(LEFT));
     if ((*empty) == p4)
            return result = std::shared_ptr<board::SLIDE_DIRECTIONS> (new SLIDE_DIRECTIONS(RIGHT));


    return result;
}

EmptyBoard::EmptyBoard(const Dimension2D &d):
    PuzzleBoard(d)
{

}

void EmptyBoard::setCorrectAlignment()
{
    puzzle::EmptyPuzzle p;
    fillWith(p);
}

std::shared_ptr<PuzzleBoard> EmptyBoard::clone() const
{
    return std::shared_ptr<PuzzleBoard>(new EmptyBoard(*this));
}

BoardType EmptyBoard::getBoardType()
{
    return BoardType::EMPTY;
}

EmptyBoard::~EmptyBoard()
{
}

std::shared_ptr<PuzzleBoard> EmptyBoard::getBoardToCompare()
{
    if (correctlyAlignedBoards == 0)
    {
        correctlyAlignedBoards = Dimension2DToEmptyBoardMapPtr(new map <Dimension2D,shared_ptr<EmptyBoard> >);
    }
    Dimension2D dims = getDimensions();
    if (correctlyAlignedBoards->find(dims) == correctlyAlignedBoards->end())
    {
        shared_ptr<EmptyBoard> e(new EmptyBoard(dims));
        (*correctlyAlignedBoards)[dims] = e;
    }
    return (*correctlyAlignedBoards)[dims];
}

OrderedBoard::OrderedBoard(const Dimension2D &d):
    PuzzleBoard(d)
{
}

BoardType OrderedBoard::getBoardType()
{
    return BoardType::ORDERED;
}

OrderedBoard::~OrderedBoard()
{
}

IntPuzzleBoard::IntPuzzleBoard(const Dimension2D &d):
    OrderedBoard(d)
{
    setCorrectAlignment();
}

void IntPuzzleBoard::setCorrectAlignment()
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

std::shared_ptr<PuzzleBoard> IntPuzzleBoard::clone() const
{
    return std::shared_ptr<PuzzleBoard>(new IntPuzzleBoard(*this));
}

IntPuzzleBoard::~IntPuzzleBoard()
{
}

std::shared_ptr<PuzzleBoard> IntPuzzleBoard::getBoardToCompare()
{
    if (correctlyAlignedBoards == 0)
    {
        correctlyAlignedBoards = Dimension2DToIntPuzzleBoardMapPtr(new map<Dimension2D, shared_ptr<IntPuzzleBoard> > );
    }
    Dimension2D dims = getDimensions();
    if (correctlyAlignedBoards->find(dims) == correctlyAlignedBoards->end())
    {
        shared_ptr<IntPuzzleBoard> e(new IntPuzzleBoard(dims));
        (*correctlyAlignedBoards)[dims] = e;
    }
    return (*correctlyAlignedBoards)[dims];
}

std::shared_ptr<Position2D> PuzzlePointerPool::getPointerForObject(const Position2D &pos)
{
    u_int i;
    bool found = false;

    for (i=0; i<points.size(); i++)
    {
        if (*points[i] == pos)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        return points[i];

    } else
    {
        return createNew(pos);
    }
}

std::shared_ptr<Puzzle> PuzzlePointerPool::getPointerForObject(const Puzzle &puzzle)
{
    u_int i;
    bool found = false;

    for (i=0; i<puzzles.size(); i++)
    {
        if (puzzle == (*puzzles[i]))
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        return puzzles[i];

    } else
    {
        return createNew(puzzle);
    }
}

PuzzlePointerPool::~PuzzlePointerPool()
{
}

std::shared_ptr<Position2D> PuzzlePointerPool::createNew(const Position2D &pos)
{
    std::shared_ptr<Position2D> p(pos.clone());
    points.push_back(p);
    return p;
}

std::shared_ptr<Puzzle> PuzzlePointerPool::createNew(const Puzzle &puz)
{
    std::shared_ptr<Puzzle> p(puz.clone());
    puzzles.push_back(p);
    return p;
}



}
