#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include <map>
#include <vector>
#include <memory>
#include <set>
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

class PuzzleBoardState;

struct PuzzleBoardStateParams
{
    PuzzleBoardStateParams();
    std::shared_ptr<PuzzleBoardState> cameFrom;
    std::shared_ptr<board::PuzzleBoard> currentBoard;

    u_int movesMadeSoFar;
    u_int priority;
    std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState;
};

class PuzzleBoardState
{
public:
    PuzzleBoardState(const PuzzleBoardStateParams &params);

    const std::shared_ptr<PuzzleBoardState> cameFrom;
    const std::shared_ptr<board::PuzzleBoard> currentBoard;

    const u_int movesMadeSoFar;
    const u_int priority;
    const std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState;


    virtual ~PuzzleBoardState();
};

typedef const std::vector < std::shared_ptr<PuzzleBoardState > >::iterator StateListIterator;

class StateManager
{
public:
    StateManager();
    void addState(std::shared_ptr<PuzzleBoardState >);
    StateListIterator getStateWithLowestPriority();
    void setNextCurrentState();
    const std::shared_ptr<PuzzleBoardState > getCurrentState();
    u_int getNumStates();
    bool hasThisStateBeenChecked(std::shared_ptr<PuzzleBoardState> state);
    void transferToClosedList(std::shared_ptr<PuzzleBoardState> state);

    void clear();

    virtual ~StateManager();
    u_int getOpenStateSize() const;
    u_int getClosedStateSize() const;


protected:
    std::vector < std::shared_ptr<PuzzleBoardState > > openStateList;
    std::set < std::shared_ptr<PuzzleBoardState > > closedList;
    std::shared_ptr<PuzzleBoardState > currentState;


};

class PuzzleShuffler;

typedef std::shared_ptr< std::vector < std::shared_ptr<PuzzleBoardState > > > StateVectorPtr;
class PuzzleSolver
{
public:
    PuzzleSolver();
    void newSearch();
    void solve() ;
    void setBoardToSolve(board::PuzzleBoard&) ;
    const std::vector<board::SLIDE_DIRECTIONS> getResult();
    const std::shared_ptr<PuzzleBoardState > getCurrentState();
    const StateVectorPtr getAvailableStates(const std::shared_ptr<PuzzleBoardState> currentState);
    bool isSolved();
    bool isSolved(const PuzzleBoardState &p);

    virtual ~PuzzleSolver(){}
    u_int getStatesChecked() const;

    void setStateCheckLimit(const u_int &value);

    void setPriorityFunction(const PriorityFunction &value);
    int calculatePriority(board::PuzzleBoard &, int moveCount);

protected:
    PriorityFunction priorityFunction;
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
