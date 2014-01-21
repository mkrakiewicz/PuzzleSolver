#include "stdafx.h"
#include "puzzleboard.h"
#include "config.h"
#include "puzzlecreator.h"
#include "qpuzzleboard.h"


using namespace board;

QPuzzleBoard::QPuzzleBoard()
{
}


//void QPuzzleBoard::createLabelPuzzles()
//{


//}


void QPuzzleBoardCreator::createBoard(/*const Dimension2D &boardSize*/)
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
}
