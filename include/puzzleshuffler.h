#ifndef PUZZLESHUFFLER_H
#define PUZZLESHUFFLER_H

#include <memory>

namespace boards {
    class PuzzleBoard;
}

class PuzzleShuffler
{
public:
    PuzzleShuffler();
    void setInitialBoard(boards::PuzzleBoard &b);
    void setSteps(int);
    void shuffle();
    std::shared_ptr<boards::PuzzleBoard> getResult();

    virtual ~PuzzleShuffler(){}
protected:
    std::shared_ptr<boards::PuzzleBoard> initial;
    std::shared_ptr<boards::PuzzleBoard> result;
    int steps;
};

#endif // PUZZLESHUFFLER_H
