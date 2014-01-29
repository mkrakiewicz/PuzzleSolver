#include "stdafx.h"
#include "puzzleboard.h"
#include "config.h"
#include "qpuzzlecreator.h"
#include "qpuzzleboard.h"
#include "qpuzzle.h"
#include "puzzle.h"
#include "position2d.h"
#include "puzzlesolver.h"
#include "exceptions.h"



using namespace board;
using namespace puzzle;

QPuzzleBoard::QPuzzleBoard(QWidget *parent, const board::Dimension2D &dimensions):
    QWidget(parent),

    dimensions(new Dimension2D(dimensions)),
     solver(0),
    puzzleObjects(new std::map < u_int,QLabelPuzzle* >),
    innerBoard(new IntPuzzleBoard(dimensions))

{
    animationRunning = false;
}

const Dimension2D &QPuzzleBoard::getDimensions()
{
    const Dimension2D& p = *dimensions;

    return p;
}

void QPuzzleBoard::setObjectForPuzzle(QLabelPuzzle* puzzle)
{
    auto val = puzzle->getInnerPuzzle()->Value;
    (*puzzleObjects)[val] = puzzle;
}

QLabelPuzzle *QPuzzleBoard::getPuzzle(u_int Value)
{
    return (*puzzleObjects)[Value];
}

const Position2D & QPuzzleBoard::getPosInBoard(/*const std::shared_ptr<QLabelPuzzle> puzzle*/)
{
//    u_int p = (*PuzzleObjToIDPtr)[puzzle];
    Position2D g(0,3);
    Position2D &h =g;
    return h;
}

bool QPuzzleBoard::trySlidePuzzle(QPuzzle & puzzle)
{

    auto p = puzzle.getInnerPuzzle();

    auto direction = innerBoard->getSlideDir(*p);

    if (direction == 0)
        return false;

    if (innerBoard->slidePuzzle(*direction))
    {
        puzzle.applyPuzzleAnimation(*direction);
        return true;
    }

    return false;
}

//bool QPuzzleBoard::trySlidePuzzle(SLIDE_DIRECTIONS direction)
//{
//    auto p = puzzle.getInnerPuzzle();
//    if (innerBoard->slidePuzzle(direction))
//    {
//        puzzle.applyPuzzleAnimation(direction);
//        return true;
//    }

//    return false;
//}

//Position2D QPuzzleBoard::directionToPosition(const Position2D &initialPos, const SLIDE_DIRECTIONS &direction)
//{
//    Position2D posAfterSlide;
//    switch (direction)
//    {
//        case UP:
//        posAfterSlide = Position2D(initialPos->X,initialPos->Y+1);
//        break;
//        case DOWN:
//        posAfterSlide = Position2D(initialPos->X,initialPos->Y-1);
//        break;
//        case LEFT:
//        posAfterSlide = Position2D(initialPos->X+1,initialPos->Y);
//        break;
//        case RIGHT:
//        posAfterSlide = Position2D(initialPos->X-1,initialPos->Y);
//        break;
//    }
//    return posAfterSlide;
//}

QLabelPuzzle *QPuzzleBoard::getSlidablePuzzle(const SLIDE_DIRECTIONS &direction)
{
    auto p = innerBoard->getEmptyPuzzlePos();
    Position2D desired = innerBoard->determineEmptyPosAfterSlide(direction);

    if (innerBoard->isValidPos(desired))
    {
        auto puzzl = innerBoard->getPuzzle(desired);
        if (puzzl->getType() == puzzle::PUZZLE_TYPES::OBJECT)
        {
            std::shared_ptr<IntPuzzle> p = std::dynamic_pointer_cast<IntPuzzle> (puzzl->clone());
            int val = p->Value;
            return  getPuzzle(val);
        }
        else return 0;
    }else return 0;
}

bool QPuzzleBoard::slideInnerPuzzle(SLIDE_DIRECTIONS direction)
{
     if (innerBoard->slidePuzzle(direction))
         return true;
     return false;
}

void QPuzzleBoard::setAnimationStarted()
{
    animationRunning = true;
}

void QPuzzleBoard::setAnimationFinished()
{
    animationRunning = false;
}

bool QPuzzleBoard::hasAnimationFinished()
{
    return !animationRunning;
}

void QPuzzleBoard::deleteInnerObjects()
{
    std::vector<QPuzzle*> pointers;
    for (std::map < u_int,QLabelPuzzle* >::iterator it=puzzleObjects->begin(); it!=puzzleObjects->end(); ++it)
    {
        QPuzzle* obj = it->second;
        pointers.push_back(obj);
    }

    puzzleObjects->clear();
    for (u_int i=0; i<pointers.size(); i++)
    {
        QPuzzle* obj = pointers[i];
        delete obj;
    }
}

bool QPuzzleBoard::solveBoard()
{
    IntPuzzleBoard toSolve = *innerBoard;
    solver = std::shared_ptr  <PuzzleSolver>  (new PuzzleSolver(toSolve.getDimensions()));
    solver->setBoardToSolve(toSolve);
    solver->solve();
    return solver->isSolved();
}

IntPuzzleBoardPtr QPuzzleBoard::getInnerBoard()
{
    return innerBoard;
}

QPuzzleBoard::~QPuzzleBoard()
{

}


void QPuzzleBoard::on_animationFinished()
{
    setAnimationFinished();
}


QPuzzleBoard* QPuzzleBoardCreator::createBoard()
{

    QPuzzleBoard* qp = 0;
    if (parentForBoard)
        qp = new QPuzzleBoard(parentForBoard, *dimensions);
    else
        qp = new QPuzzleBoard(0, *dimensions);

    return qp;
}

QPuzzleBoardCreator::~QPuzzleBoardCreator()
{
}


QPuzzleBoardCreator::QPuzzleBoardCreator():
    dimensions(0),
    parentForBoard(0)
{
}

void QPuzzleBoardCreator::setParent(QWidget *parentForBoard)
{
    this->parentForBoard = parentForBoard;
}

void QPuzzleBoardCreator::setDimensions(const Dimension2D &dims)
{
    dimensions = std::shared_ptr<board::Dimension2D>(new Dimension2D(dims));
}


