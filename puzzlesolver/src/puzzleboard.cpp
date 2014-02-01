#include "stdafx.h"

#include "puzzleboard.h"
#include <sstream>
#include <map>
#include <cmath>

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

Puzzle *PuzzlePositionContainer::findPuzzle(Position2D &point)
{
    Position2D* pos = pool.getPointerForObject(point);
    auto result = positionToPuzzle.find(pos);
    if ( result == positionToPuzzle.end() ) {
        throw Exception("Position not found? object should have been created!");
    }
    return result->second;

}

Puzzle* PuzzlePositionContainer::findPuzzle(u_int val)
{
    IntPuzzle a(val);
    Puzzle* puz = pool.getPointerForObject(a);
    return puz;

}

Position2D* PuzzlePositionContainer::findPoint(Puzzle &puzzle)
{
    auto result = puzzleToPosition.find(pool.getPointerForObject(puzzle));
    if ( result == puzzleToPosition.end() ) {
        return 0;
    } else return result->second;
}

Position2D *PuzzlePositionContainer::getEmptyPuzzlePos()
{
    return emptyPuzzlePos;
}

void PuzzlePositionContainer::swap(Position2D &pos1, Position2D &pos2)
{
    puzzle::Puzzle* puz1 = findPuzzle(pos1);
    puzzle::Puzzle* puz2 = findPuzzle(pos2);
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

Puzzle* PuzzleBoard::getPuzzle(Position2D &pos)
{
    auto p = puzzles.findPuzzle(pos);
    if (p == 0) {
        stringstream s;
        s << "Puzzle Not found? Requested position:";
        s << pos.toString() << endl;
        throw Exception(s.str());
    }
    return p;
}

Puzzle* PuzzleBoard::getPuzzle(u_int value)
{
    return puzzles.findPuzzle(value);
}

Position2D* PuzzleBoard::getPuzzlePos(Puzzle &puzzle)
{
    return puzzles.findPoint(puzzle);
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
            Puzzle* p1 = getPuzzle(pos);
            if (e.operator ==(*p1))
                continue;
            Puzzle* p2 = reference->getPuzzle(pos);
            if (p1->operator !=(*p2))
                wrong++;
        }
    }
    return wrong;
}

u_int PuzzleBoard::getSumOfDistances()
{
    u_int sum = 0;
    EmptyPuzzle e;
    auto reference = getBoardWithCorrectAlignment();
    for (u_int x=0; x<horizontalSize; x++)
    {
        for (u_int y=0; y<verticalSize; y++)
        {
            Position2D pos(x,y);
            auto thisPuzzle = (getPuzzle(pos));
            if ((*thisPuzzle) == e)
                continue;
            auto goalPuzzlePos = reference->getPuzzlePos(*thisPuzzle);
            if (pos != (*goalPuzzlePos))
            {
                sum += (abs(pos.X - goalPuzzlePos->X));
                sum += (abs(pos.Y - goalPuzzlePos->Y));
            }

        }
    }
    return sum;
}

int PuzzleBoard::calculateHammingPriority(int movesMadeSoFar)
{
    int misaligned = getNumberOfPuzzlesInWrongPosition();
    return misaligned + movesMadeSoFar;
}

int PuzzleBoard::calculateManhattanPriority(int movesMadeSoFar)
{
    int distance = getSumOfDistances();
    return distance + movesMadeSoFar;
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

std::shared_ptr<Position2D> PuzzleBoard::determineEmptyPosAfterSlide(const SLIDE_DIRECTIONS &dir)
{
    Position2D emptyPos = *puzzles.getEmptyPuzzlePos();

    switch(emptyPuzzleSlideDirection(dir))
    {
    case UP:
        return std::shared_ptr<Position2D>(new Position2D(emptyPos.X, emptyPos.Y-1));
    case DOWN:
        return std::shared_ptr<Position2D>(new Position2D(emptyPos.X, emptyPos.Y+1));
    case LEFT:
        return std::shared_ptr<Position2D>(new Position2D(emptyPos.X-1, emptyPos.Y));
    case RIGHT:
        return std::shared_ptr<Position2D>(new Position2D(emptyPos.X+1, emptyPos.Y));

    default:
        throw Exception("Forgot to implement new direction for determineNewSlidePos");
    }
}

bool PuzzleBoard::slidePuzzle(const SLIDE_DIRECTIONS &dir)
{
    Position2D* emptyPos = puzzles.getEmptyPuzzlePos();
    auto newPos = determineEmptyPosAfterSlide(dir);

    if (!isValidPos(*newPos))
        return false;

    puzzles.swap(*emptyPos,*newPos);
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
    return std::make_shared<EmptyBoard>(*this);
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
    return std::make_shared<IntPuzzleBoard>(*this);
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

Position2D* PuzzlePointerPool::getPointerForObject(Position2D &pos)
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
        return points[i].get();

    } else
    {
        return createNew(pos);
    }
}

Puzzle *PuzzlePointerPool::getPointerForObject(Puzzle &puzzle)
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
        return puzzles[i].get();

    } else
    {
        return createNew(puzzle);
    }
}

PuzzlePointerPool::~PuzzlePointerPool()
{
}

 Position2D* PuzzlePointerPool::createNew(Position2D &pos)
{
    std::shared_ptr<Position2D> p(pos.clone());
    points.push_back(p);
    return p.get();
}

Puzzle* PuzzlePointerPool::createNew(Puzzle &puz)
{
    std::shared_ptr<Puzzle> p(puz.clone());
    puzzles.push_back(p);
    return p.get();
}



}
