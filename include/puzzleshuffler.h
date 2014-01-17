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
    class Dimension2D;
}

class Position2D;
class string;

typedef std::shared_ptr<board::PuzzleBoard>  PuzzleBoardSharedPtr; // because it is too long


class PuzzleShuffler
{
public:
    PuzzleShuffler();

    template <typename T> static PuzzleBoardSharedPtr createShuffledBoard(const board::Dimension2D &dim, float percentageShuffled = 0.5f)
    {
        PuzzleShuffler s;
        T board(dim);
        s.setBoardToShuffle(board);
        s.setMinimumShuffledPuzzles(percentageShuffled);
        s.shuffle();
        return s.getResult();
    }

    void setBoardToShuffle(board::PuzzleBoard &b);
    void setShuffleMoves(int);
    void setMinimumShuffledPuzzles(float);
    float getPercentageShuffled();
    void shuffle() throw();
    std::shared_ptr<board::PuzzleBoard> getResult();
    void verifyBoard() throw();
    std::vector < std::map<board::SLIDE_DIRECTIONS, std::string> > getStepHistory();
    std::vector<Position2D> getEmptyMovementHistory();
    void staticInit();

    virtual ~PuzzleShuffler(){}
protected:
    int shuffleSteps;
    float shufflePercentage;

    void shuffleByPercentage();
    void shuffleBySteps();
    bool tryMoveInAllDirections();
    bool wasEmptyThere(Position2D &pos);
    bool trySlide(board::SLIDE_DIRECTIONS &direction);
    void saveEmptyMovementHistory(Position2D &pos);
    void resetForNewPass();
    board::SLIDE_DIRECTIONS getRandomDirection();

    std::shared_ptr<board::PuzzleBoard> initialBoard;
    std::shared_ptr<board::PuzzleBoard> boardToShuffle;
    std::shared_ptr < std::vector<std::map<board::SLIDE_DIRECTIONS, std::string>>  > slideHistory;

private:
    std::shared_ptr< std::set<Position2D> > wasThere;
    std::shared_ptr< std::vector<Position2D> > positionHistory;

    static std::vector<board::SLIDE_DIRECTIONS> directions;


};

#endif // PUZZLESHUFFLER_H
