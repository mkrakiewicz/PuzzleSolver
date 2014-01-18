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

    const std::shared_ptr<PuzzleBoardState> cameFrom;
    const std::shared_ptr<board::PuzzleBoard> currentBoard;

    const u_int movesMadeSoFar;
    const u_int hammingPriority;

    virtual ~PuzzleBoardState();

protected:
    int calculateHammingPriority();

};

class SolveStep
{
public:
    SolveStep(board::SLIDE_DIRECTIONS slideDirection);
    const board::SLIDE_DIRECTIONS slideDirection;
    virtual ~SolveStep();
};


class StateManager
{
public:
    StateManager();
    void addState(std::shared_ptr<PuzzleBoardState >);
    std::shared_ptr<PuzzleBoardState> popStateWithLowestPriority();
    void clear();

    virtual ~StateManager();
protected:
    std::vector < std::shared_ptr<PuzzleBoardState > > stateList;

};

class PuzzleShuffler;


class PuzzleSolver
{
public:
    PuzzleSolver(const board::Dimension2D&dim);
    void newSearch();
    void solve();
    void setBoardToSolve(board::PuzzleBoard&) throw();
    std::vector<SolveStep> getSolveSteps();


    virtual ~PuzzleSolver(){}
protected:
    std::shared_ptr<board::Dimension2D> dimensionOfBoards;
    std::shared_ptr<board::PuzzleBoard> boardToSolve;
    std::shared_ptr< StateManager > stateManager;

    std::shared_ptr< std::vector<SolveStep> > steps;


};

#endif // PUZZLESOLVER_H
