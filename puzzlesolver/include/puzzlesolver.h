#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include <map>
#include <vector>
#include <memory>
#include <set>
#include "enums.h"
#ifdef MY_DEBUG
#include "dbg.h"
#endif

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
    PuzzleBoardStateParams(std::shared_ptr<PuzzleBoardState> cameFrom,
                           std::shared_ptr<board::PuzzleBoard> currentBoard,
                           u_int movesMadeSoFar,
                           u_int priority,
                           std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState);
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

typedef std::multimap <u_int, std::shared_ptr<PuzzleBoardState > >::iterator StateListIterator;

class StateManager
{
public:
    StateManager();
    void addState(std::shared_ptr<PuzzleBoardState >);
    StateListIterator getStateWithLowestPriority();
    void setNextCurrentState();
    const StateListIterator getCurrentStateIterator();
    u_int getNumStates();
    bool hasThisStateBeenChecked(std::shared_ptr<PuzzleBoardState> &state);
    void transferToClosedList(StateListIterator state);

    void clear();

    virtual ~StateManager();
    u_int getOpenStateSize() const;
    u_int getClosedStateSize() const;

    std::multimap <u_int, std::shared_ptr<PuzzleBoardState > > openStateList;

    bool isEmptyCurrent();
protected:
    std::set < std::shared_ptr<PuzzleBoardState > > closedList;
    StateListIterator currentStateIt;


};

class PuzzleShuffler;

typedef std::shared_ptr< std::vector < std::shared_ptr<PuzzleBoardState > > > StateVectorPtr;
class PuzzleSolver
{
#ifdef MY_DEBUG
    Avg beforeloop;
    Avg clone;
    Avg slide;
    Avg stateparam;
    Avg checkchecked;
    Avg push;
    Avg all;
    Avg firstHalf;
    Avg secondHalf;
    Avg innerLoop;
    Avg calcPrior;
#endif

public:
    PuzzleSolver();
    void newSearch();
    void solve() ;
    void setBoardToSolve(board::PuzzleBoard&) ;
    const std::vector<board::SLIDE_DIRECTIONS> getResult();
    const std::shared_ptr<PuzzleBoardState > getCurrentState();
    const StateVectorPtr getAvailableStates(const std::shared_ptr<PuzzleBoardState> &currentState);
    bool isSolved();
    bool isSolved(const PuzzleBoardState &p);

    virtual ~PuzzleSolver(){}
    u_int getStatesChecked() const;

    void setStateCheckLimit(const u_int &value);

    void setPriorityFunction(const PriorityFunction &value);
    int calculatePriority(board::PuzzleBoard &, const int &moveCount);

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
