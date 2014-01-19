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
    PuzzleBoardState(u_int movesMadeSoFar, std::shared_ptr<PuzzleBoardState> cameFrom,  board::PuzzleBoard & currentBoard,  std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState);

    const std::shared_ptr<PuzzleBoardState> cameFrom;
    const std::shared_ptr<board::PuzzleBoard> currentBoard;

    const u_int movesMadeSoFar;
    const u_int hammingPriority;
    const std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState;


    virtual ~PuzzleBoardState();

protected:
    int calculateHammingPriority();

};

typedef const std::vector < std::shared_ptr<PuzzleBoardState > >::iterator StateListIterator;

class StateManager
{
public:
    StateManager();
    void addState(std::shared_ptr<PuzzleBoardState >);
    StateListIterator getStateWithLowestPriority();
//    void setNextState
    void setNextCurrentState();
    const std::shared_ptr<PuzzleBoardState > getCurrentState();
    u_int getNumStates();

    void clear();

    virtual ~StateManager();
protected:
    std::vector < std::shared_ptr<PuzzleBoardState > > stateList;
    std::shared_ptr<PuzzleBoardState> currentState;

};

class PuzzleShuffler;


class PuzzleSolver
{
public:
    PuzzleSolver(const board::Dimension2D&dim);
    void newSearch();
    void solve();
    void setBoardToSolve(board::PuzzleBoard&) throw();
    const std::vector<board::SLIDE_DIRECTIONS> getResult();
    const std::shared_ptr<PuzzleBoardState > getCurrentState();
    const std::vector < std::shared_ptr<PuzzleBoardState > > getAvailableStates();


    virtual ~PuzzleSolver(){}
protected:
    void setGoalBoard();
    bool isSolved();
    void recursiveAddSteps(std::shared_ptr<PuzzleBoardState > parent);
    std::shared_ptr<board::Dimension2D> dimensionOfBoards;
    std::shared_ptr<board::PuzzleBoard> boardToSolve;
    std::shared_ptr< StateManager > stateManager;
    std::shared_ptr<board::PuzzleBoard> goalBoard;
    std::shared_ptr< std::vector<board::SLIDE_DIRECTIONS> > steps;
};

#endif // PUZZLESOLVER_H
