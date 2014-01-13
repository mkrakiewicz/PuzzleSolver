#ifndef PUZZLESHUFFLER_H
#define PUZZLESHUFFLER_H

#include <memory>
#include <set>
#include <map>
#include <vector>
#include "stdafx.h"
#include "enums.h"

namespace board {
    class PuzzleBoard;
}

class Position2D;
class string;

class PuzzleShuffler
{
public:
    PuzzleShuffler();
    void setInitialBoard(board::PuzzleBoard &b);
    void setSteps(int);
    void shuffle(int = 100) throw();
    std::shared_ptr<board::PuzzleBoard> getResult();
    void verifyBoard() throw();
    std::vector < std::map<board::SLIDE_DIRECTIONS, std::string> > getStepHistory();
    std::vector<Position2D> getEmptyMovementHistory();
    void staticInit();

    virtual ~PuzzleShuffler(){}
protected:
    bool tryMoveInAllDirections();
    bool wasEmptyThere(Position2D &pos);
    bool trySlide(board::SLIDE_DIRECTIONS &direction);
    void saveEmptyMovementHistory(Position2D &pos);
    void resetForNewPass();
    board::SLIDE_DIRECTIONS getRandomDirection();

    std::shared_ptr < std::vector<std::map<board::SLIDE_DIRECTIONS, std::string>>  > slideHistory;


    std::shared_ptr<board::PuzzleBoard> initial;
    std::shared_ptr<board::PuzzleBoard> result;
    int steps;


private:
    std::shared_ptr< std::set<Position2D> > wasThere;
    std::shared_ptr< std::vector<Position2D> > positionHistory;

    static std::vector<board::SLIDE_DIRECTIONS> directions;


};

#endif // PUZZLESHUFFLER_H
