#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include <vector>
#include <memory>
#include "enums.h"

#define DEBUG_PUZZLESOLVER

namespace board {
    class PuzzleBoard;
    class Dimension2D;

}

class PuzzleBoardState
{
public:
    PuzzleBoardState(u_int movesMadeSoFar,  const board::PuzzleBoard & currentBoardState);
    const u_int movesMadeSoFar;
    const std::shared_ptr<board::PuzzleBoard> currentBoardState;
};

class SolveStep
{
public:
    SolveStep(board::SLIDE_DIRECTIONS slideDirection);
    const board::SLIDE_DIRECTIONS slideDirection;
};

class PuzzleShuffler;

class PuzzleSolver
{
public:
    PuzzleSolver(const board::Dimension2D&dim);
    void solve();
    void setBoardToSolve(board::PuzzleBoard&) throw();
    std::shared_ptr<board::PuzzleBoard> getResult();
    std::vector<SolveStep> getSolveSteps();
    static int calculateHammingPriorityFor( std::shared_ptr<PuzzleBoardState> state);

#ifdef DEBUG_PUZZLESOLVER
    void _debug_steps(PuzzleShuffler &p);
//    void _debug_set_next_step();
#endif

    virtual ~PuzzleSolver(){}
protected:
//    std::shared_ptr<board::PuzzleBoardState> currentState;
    std::shared_ptr< std::vector<SolveStep> > steps;

    std::shared_ptr<board::PuzzleBoard> boardToSolve;
    std::shared_ptr<board::PuzzleBoard> result;

    std::shared_ptr<board::Dimension2D> dimensionOfBoards;

};

#endif // PUZZLESOLVER_H
