#include "stdafx.h"

#include <set>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "puzzleshuffler.h"
#include "puzzleboard.h"
#include "exceptions.h"
#include "position2d.h"
#include "puzzle.h"
#include "enums.h"

using namespace std;
using namespace board;
using namespace puzzle;



PuzzleShuffler::PuzzleShuffler():
    initialBoard(0),
    boardToShuffle(0),
    slideHistory(new VectorOfSlideDirToStringMaps ),
    wasThere(new vector<Position2D>),
    positionHistory(new std::vector <Position2D>)
{
    srand (time(NULL));
    setShuffleMoves(100);
}

void PuzzleShuffler::setBoardToShuffle(PuzzleBoard &b)
{
    initialBoard = std::shared_ptr<board::PuzzleBoard>(b.clone());
    boardToShuffle = std::shared_ptr<board::PuzzleBoard>(b.clone());
}

void PuzzleShuffler::setShuffleMoves(int movementSteps)
{
    if (movementSteps != 0) {
        this->shuffleSteps = movementSteps;
        this->shufflePercentage = 0;
    }
}

void PuzzleShuffler::setMinimumShuffledPuzzles(float percentage)
{
    if (percentage != 0) {
        this->shufflePercentage = (percentage > 1.0f ? 1.0f : percentage);
        this->shuffleSteps = 0;
    }
}

float PuzzleShuffler::getPercentageShuffled()
{
    u_int different =  boardToShuffle->getNumberOfPuzzlesInWrongPosition();
    int total = boardToShuffle->getMultipliedDimensions() - 1;
    float result = (float)different/total;
    return result;
}


bool PuzzleShuffler::tryMoveInAllDirections()
{
    for (u_int i=0; i<(PuzzleBoard::directions).size(); i++)
    {
        SLIDE_DIRECTIONS dir = getRandomDirection();
            bool success = trySlide(dir);
            if (success)
              return true;
    }

    return false;
}

bool PuzzleShuffler::tryMoveInNewRandomPos()
{
    for (int i=0; i<10; i++)
    {
        auto dir = getRandomDirection();
        auto after = boardToShuffle->determineEmptyPosAfterSlide(dir);
        if (boardToShuffle->isValidPos(*after) && (!wasEmptyThere(*after)))
        {
            if (trySlide(dir))
                return true;
            else continue;
        }
    }
    return false;
}

bool PuzzleShuffler::trySlide(SLIDE_DIRECTIONS &direction)
{
    if (boardToShuffle->slidePuzzle(direction))
    {
        saveEmptyMovementHistory(*boardToShuffle->getEmptyPuzzlePos());

        std::map<board::SLIDE_DIRECTIONS, std::string> tmp;
        std::string s;
        switch (direction)
        {
            case UP:
            s="UP";
            break;
            case DOWN:
            s="DOWN";
            break;
            case LEFT:
            s="LEFT";
            break;
            case RIGHT:
            s="RIGHT";
        }
        tmp[direction] = s;
        slideHistory->push_back(tmp);
        return true;
    }
    return false;
}

void PuzzleShuffler::saveEmptyMovementHistory(Position2D &pos)
{
    wasThere->push_back(pos);
    positionHistory->push_back(pos);
}

bool PuzzleShuffler::wasEmptyThere(Position2D &pos)
{
    if(std::find(wasThere->begin(), wasThere->end(), pos)!=wasThere->end()){
          return true;
    }
    return false;

}

void PuzzleShuffler::shuffle()
{
    verifyBoard();
    resetForNewPass();
    Position2D empty = *boardToShuffle->getEmptyPuzzlePos();
    saveEmptyMovementHistory(empty);

    if ((shuffleSteps != 0) && (shufflePercentage == 0))
                shuffleBySteps();
    else if ((shuffleSteps == 0) && (shufflePercentage != 0))
                shuffleByPercentage();
    else
        throw Exception("There are invalid parameters either steps or % must be zero.");


}

std::shared_ptr<PuzzleBoard> PuzzleShuffler::getResult()
{
    return boardToShuffle;
}

void PuzzleShuffler::verifyBoard()
{
    Dimension2D dims = boardToShuffle->getDimensions();

    if ((dims.horizontalSize+dims.verticalSize) < 3)
        throw Exception("Board must be at least 2x1");

    int emptyFound = 0;
    for (u_int y=0; y<boardToShuffle->verticalSize; y++)
    {
        for (u_int x=0; x<boardToShuffle->horizontalSize; x++)
        {
            Position2D pos(x,y);
            if (boardToShuffle->getPuzzle(pos)->getType() == puzzle::EMPTY)
                emptyFound++;
        }

    }

    if (emptyFound == 0)
        throw Exception("There was empty puzzle in the board ");

    if (emptyFound > 1)
        throw Exception("There was more than 1 empty puzzle in the board");

    if ((shufflePercentage + shuffleSteps) == 0)
        throw Exception("There must be either steps set or percentage for shuffling");

}

VectorOfSlideDirToStringMaps PuzzleShuffler::getStepHistory()
{
    return *(this->slideHistory);
}

//typedef std::vector < std::map<board::SLIDE_DIRECTIONS, std::string> > VectorOfSlideDirToStringMaps;
std::shared_ptr<std::vector<board::SLIDE_DIRECTIONS> > PuzzleShuffler::getStepsOnly()
{
    std::shared_ptr<std::vector<board::SLIDE_DIRECTIONS> > steps(new std::vector<board::SLIDE_DIRECTIONS> );
    for (u_int i=0; i<slideHistory->size(); i++)
    {
        std::map<board::SLIDE_DIRECTIONS, std::string> map = (*slideHistory)[i];
        steps->push_back((*map.begin()).first);
    }
    return steps;
}

std::vector<Position2D> PuzzleShuffler::getEmptyMovementHistory()
{

    return std::vector<Position2D>(*positionHistory);
}


void PuzzleShuffler::resetForNewPass()
{
    wasThere->clear();
}

SLIDE_DIRECTIONS PuzzleShuffler::getRandomDirection()
{
    return PuzzleBoard::directions[rand()%4];
}


void PuzzleShuffler::shuffleByPercentage()
{
    auto count = 0;
    int strikes = 0;

    float shuffled = getPercentageShuffled();
    while(shuffled <= shufflePercentage)
    {
        if ( count > 50)
            throw Exception("More than 50 moves, exiting .");

        if (tryMoveInNewRandomPos())
        {
            shuffled = getPercentageShuffled();
            count++;
        } else strikes++;
        if (strikes == 3)
        {
            wasThere->clear();
            strikes = 0;
        }


    }
}

void PuzzleShuffler::shuffleBySteps()
{
    int strikes = 0;
    for (int i=0; i<shuffleSteps; i++)
    {
       if (!tryMoveInNewRandomPos())
       {    strikes++;
       }
       if (strikes == 3)
       {
           wasThere->clear();
           strikes = 0;
       }
    }
}


