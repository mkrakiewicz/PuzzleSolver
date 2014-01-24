#include "stdafx.h"
#include "puzzleboard.h"
#include "config.h"
#include "puzzlecreator.h"
#include "qpuzzleboard.h"
#include "qpuzzle.h"
#include "puzzle.h"
#include "position2d.h"
#include "puzzlesolver.h"



using namespace board;

QPuzzleBoard::QPuzzleBoard(QWidget *parent, const board::Dimension2D &dimensions):
    QWidget(parent),

    dimensions(new Dimension2D(dimensions)),
     solver(0),
    puzzleObjects(new std::map < u_int,QLabelPuzzle* >),
    innerBoard(new IntPuzzleBoard(dimensions)),
    animationRunning(false)

{
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

const QLabelPuzzle *QPuzzleBoard::getPuzzle(u_int Value)
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

    try {
     solver->solve();
    } catch (...)
    {
        return false;
    }

//    auto r = solver->getResult();

    return true;
}

QPuzzleBoard::~QPuzzleBoard()
{

}

void QPuzzleBoard::on_animationFinished()
{
    setAnimationFinished();
}



/*const std::shared_ptr<QLabelPuzzle> QPuzzleBoard::getPuzzle(const Position2D &pos)
{

}*/


//void QPuzzleBoard::createLabelPuzzles()
//{


//}


QPuzzleBoard* QPuzzleBoardCreator::createBoard()
{

//    puzzles->clear();
//    u_int biggerVal = 0;

//    const u_int totalPuzzles = (boardSize->verticalSize * boardSize->horizontalSize) - 1;

//    if (boardSize->horizontalSize > boardSize->verticalSize)
//        biggerVal = boardSize->horizontalSize;
//    else
//        biggerVal = boardSize->verticalSize;

//    const u_int puzzleSize = MAX_BOARD_PIXELS/biggerVal;
//    const u_int moveBy = puzzleSize;
//    PuzzleCreator pC;
//    pC.moveBy = moveBy;
//    pC.parentObject = ui->framePuzzleContainer;
//    pC.puzzleSize = puzzleSize;

//    u_int count = 1;
//    for (u_int y=0; y<boardSize->verticalSize; y++)
//    {
//        for (u_int x=0; x<boardSize->horizontalSize; x++)
//        {
//            if (count == (totalPuzzles + 1))
//                break;

//            pC.xOffsetMultiplier = x;
//            pC.yOffsetMultiplier = y;

//            auto p = pC.createPuzzle(count);
//            (*puzzles)[count] = p;

//            count++;
//        }
//    }
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


