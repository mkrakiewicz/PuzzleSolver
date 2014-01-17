#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include <map>
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
    PuzzleBoardState(u_int movesMadeSoFar, std::shared_ptr<PuzzleBoardState> cameFrom,  board::PuzzleBoard & currentBoard);
    const u_int movesMadeSoFar;
    const std::shared_ptr<PuzzleBoardState> cameFrom;
    const std::shared_ptr<board::PuzzleBoard> currentBoard;


    int calculateHammingPriorityFor(board::PuzzleBoard&);
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
    void newSearch();
    void solve();
    void setBoardToSolve(board::PuzzleBoard&) throw();
    void setCurrentState(std::shared_ptr<PuzzleBoardState> state);
    std::vector<SolveStep> getSolveSteps();

    std::shared_ptr<PuzzleBoardState> getStateWithHighestPriority();

    virtual ~PuzzleSolver(){}
protected:
//    std::multimap <u_int, std:: > currentState;

    std::shared_ptr< std::vector<SolveStep> > steps;

    std::shared_ptr<board::PuzzleBoard> boardToSolve;
    std::shared_ptr<board::Dimension2D> dimensionOfBoards;

};

#endif // PUZZLESOLVER_H
