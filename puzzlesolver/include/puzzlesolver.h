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

enum PriorityFunction{
    HAMMING,
    MANHATTAN
};

class PuzzleBoardState
{
public:
    PuzzleBoardState(u_int movesMadeSoFar, std::shared_ptr<PuzzleBoardState> cameFrom,  board::PuzzleBoard & currentBoard,  std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState, PriorityFunction p);

    const std::shared_ptr<PuzzleBoardState> cameFrom;
    const std::shared_ptr<board::PuzzleBoard> currentBoard;

    const u_int movesMadeSoFar;
    const u_int priority;
    const std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState;


    virtual ~PuzzleBoardState();

protected:
    int calculateHammingPriority();
    int calculateManhattanPriority();
    int calculatePriority();

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
    bool hasThisStateBeenChecked(const PuzzleBoardState &state);
    void setThisStateAsChecked();
    void clear();

    virtual ~StateManager();
protected:
    std::vector < std::shared_ptr<PuzzleBoardState > > stateList;
    std::shared_ptr<PuzzleBoardState> currentState;
    std::vector < std::shared_ptr<PuzzleBoardState > > alreadyChecked;


};

class PuzzleShuffler;


class PuzzleSolver
{
public:
    PuzzleSolver();
    void newSearch();
    void solve() ;
    void setBoardToSolve(board::PuzzleBoard&) ;
    const std::vector<board::SLIDE_DIRECTIONS> getResult();
    const std::shared_ptr<PuzzleBoardState > getCurrentState();
    const std::vector < std::shared_ptr<PuzzleBoardState > > getAvailableStates();
    bool isSolved();


    virtual ~PuzzleSolver(){}
    u_int getStatesChecked() const;

    void setStateCheckLimit(const u_int &value);

protected:
    void setGoalBoard();
    void recursiveAddSteps(std::shared_ptr<PuzzleBoardState > parent);
    std::shared_ptr<board::PuzzleBoard> boardToSolve;
    std::shared_ptr< StateManager > stateManager;
    std::shared_ptr<board::PuzzleBoard> goalBoard;
    std::shared_ptr< std::vector<board::SLIDE_DIRECTIONS> > steps;
    u_int statesChecked;
    u_int stateCheckLimit;
};

#endif // PUZZLESOLVER_H
