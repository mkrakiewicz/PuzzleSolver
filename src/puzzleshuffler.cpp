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

std::vector<board::SLIDE_DIRECTIONS> PuzzleShuffler::directions = {UP,DOWN,LEFT,RIGHT};


PuzzleShuffler::PuzzleShuffler():
    initialBoard(0),
    boardToShuffle(0),
    slideHistory(new std::vector < std::map<board::SLIDE_DIRECTIONS, std::string> > ),
    wasThere(new set<Position2D>),
    positionHistory(new std::vector <Position2D>)
{
    srand (time(NULL));
    setShuffleMoves(100);
}

void PuzzleShuffler::setBoardToShuffle(PuzzleBoard &b)
{
    initialBoard = b.clone();
    boardToShuffle = b.clone();
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
    int different = 0;
    for (u_int y=0; y<initialBoard->verticalSize; y++)
    {
        for (u_int x=0; x<initialBoard->horizontalSize; x++)
        {
            Position2D pos(x,y);
            auto puz1 = boardToShuffle->getPuzzle(pos);
            auto puz2 = initialBoard->getPuzzle(pos);
            if (*puz1 != *puz2)
                different++;
        }
    }
    int total = initialBoard->horizontalSize*initialBoard->verticalSize;
    float result = (float)different/total;
    return result;
}


bool PuzzleShuffler::tryMoveInAllDirections()
{
    Position2D p;

    for (u_int i=0; i<(directions).size(); i++)
    {
        SLIDE_DIRECTIONS dir = getRandomDirection();
        p = boardToShuffle->determineEmptyPosAfterSlide(dir);

            bool success = trySlide(dir);
            if (success)
              return true;
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

//        cout << "After move:" << endl;
        (boardToShuffle)->getEmptyPuzzlePos()->toString();

        return true;
    }
    return false;
}

void PuzzleShuffler::saveEmptyMovementHistory(Position2D &pos)
{
    wasThere->insert(pos);
    positionHistory->push_back(pos);
}

bool PuzzleShuffler::wasEmptyThere(Position2D &pos)
{
    if (wasThere->find(pos) == wasThere->end())
        return false;
    return true;
}

void PuzzleShuffler::shuffle() throw()
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

void PuzzleShuffler::verifyBoard() throw()
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

std::vector < std::map<board::SLIDE_DIRECTIONS, std::string> >  PuzzleShuffler::getStepHistory()
{
    return *(this->slideHistory);
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
    return directions[rand()%4];
}


void PuzzleShuffler::shuffleByPercentage()
{
    auto count = 0;

    float shuffled = 0;
    while(shuffled <= shufflePercentage)
    {
        if ( count > 10000)
            throw Exception("Iterated over 10000 times, exiting .");

       tryMoveInAllDirections();
       shuffled = getPercentageShuffled();
       count++;
    }
}

void PuzzleShuffler::shuffleBySteps()
{
    for (int i=0; i<shuffleSteps; i++)
    {
       tryMoveInAllDirections();
    }
}
