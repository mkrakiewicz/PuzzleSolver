#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include <memory>

namespace board {
    class PuzzleBoard;
}

class PuzzleSolver
{
public:
    PuzzleSolver();
    void solve();
    void setBoard(std::shared_ptr<board::PuzzleBoard>) throw();
    std::shared_ptr<board::PuzzleBoard> getResult();

    virtual ~PuzzleSolver(){}
protected:
    std::shared_ptr<board::PuzzleBoard> boardToSolve;
    std::shared_ptr<board::PuzzleBoard> result;
};

#endif // PUZZLESOLVER_H
