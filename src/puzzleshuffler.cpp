#include <set>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "puzzleshuffler.h"
#include "puzzleboard.h"
#include "exceptions.h"
#include "puzzle.h"
#include "enums.h"

using namespace std;
using namespace board;
using namespace puzzle;

std::vector<board::SLIDE_DIRECTIONS> PuzzleShuffler::directions = {UP,DOWN,LEFT,RIGHT};


PuzzleShuffler::PuzzleShuffler():
    steps(3),
    initial(0),
    result(0),
    wasThere(new set<Position2D>),
    slideHistory(new std::vector < std::map<board::SLIDE_DIRECTIONS, std::string> > ),
    positionHistory(new std::vector <Position2D>)
{
    srand (time(NULL));
}

void PuzzleShuffler::setInitialBoard(PuzzleBoard &b)
{
    initial = std::shared_ptr<PuzzleBoard>(b.clone());
}

void PuzzleShuffler::setSteps(int steps)
{
    this->steps = steps;
}


bool PuzzleShuffler::tryMoveInAllDirections()
{
    Position2D p;

    for (int i=0; i<(directions).size(); i++)
    {
        SLIDE_DIRECTIONS dir = getRandomDirection();
        p = initial->determineEmptyPosAfterSlide(dir);
//        if (!wasEmptyThere(p))
//        {
            bool success = trySlide(dir);
            if (success)
              return true;
//        }
    }

    return false;
}

bool PuzzleShuffler::trySlide(SLIDE_DIRECTIONS &direction)
{
    if (initial->slidePuzzle(direction))
    {
        saveEmptyMovementHistory(*initial->getEmptyPuzzlePos());

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
        (initial)->getEmptyPuzzlePos()->toString();

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

void PuzzleShuffler::shuffle(int passes) throw()
{
    verifyBoard();
    resetForNewPass();
    Position2D empty = *initial->getEmptyPuzzlePos();
    saveEmptyMovementHistory(empty);
    int stepsMade;
    int counter;

    for (int i=0; i<passes; i++)
    {
       tryMoveInAllDirections();
    }


}

std::shared_ptr<PuzzleBoard> PuzzleShuffler::getResult()
{
    return initial;
}

void PuzzleShuffler::verifyBoard() throw()
{
    Dimension2D dims = initial->getDimensions();
    int min = (steps > 3) ? (steps-1) : 3;
    if ((dims.horizontalSize+dims.verticalSize) < min)
        throw Exception("Board must be at least 2x1 or less by 1 from steps set.");

    int emptyFound = 0;
    for (u_int y=0; y<initial->verticalSize; y++)
    {
        for (u_int x=0; x<initial->horizontalSize; x++)
        {
            Position2D pos(x,y);
            if (initial->getPuzzle(pos)->getType() == puzzle::EMPTY)
                emptyFound++;
        }

    }

    if (emptyFound == 0)
        throw Exception("There was empty puzzle in the board ");

    if (emptyFound > 1)
        throw Exception("There was more than 1 empty puzzle in the board");

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
