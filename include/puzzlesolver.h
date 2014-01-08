#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include <memory>

namespace boards {
    class PuzzleBoard;
}

class PuzzleSolver
{
public:
    PuzzleSolver();
    void solve();
    void setBoard(std::shared_ptr<boards::PuzzleBoard>) throw();
    std::shared_ptr<boards::PuzzleBoard> getResult();

    virtual ~PuzzleSolver(){}
protected:
    std::shared_ptr<boards::PuzzleBoard> boardToSolve;
    std::shared_ptr<boards::PuzzleBoard> result;
};

#endif // PUZZLESOLVER_H
