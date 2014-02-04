#include "stdafx.h"

#include "puzzlesolver.h"
#include "puzzleboard.h"
#include "exceptions.h"
#include "puzzleshuffler.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace board;

PuzzleSolver::PuzzleSolver () :
    boardToSolve(0),
    stateManager(new StateManager()),
    steps(new vector<board::SLIDE_DIRECTIONS> ),
    statesChecked(0)
{
    priorityFunction = MANHATTAN;
}

void PuzzleSolver::newSearch()
{
    stateManager->clear();
    PuzzleBoardStateParams p;
    p.currentBoard = boardToSolve;
    p.priority = calculatePriority(*boardToSolve,0);
    shared_ptr<PuzzleBoardState> s(new PuzzleBoardState(p));
    stateManager->addState(s);
    stateManager->setNextCurrentState();
    steps->clear();
}



#ifdef MY_DEBUG

void PuzzleSolver::debugPrint()
{
    qDebug() << "\n============================================\n: ";

    qDebug() << "Mainloop: " << mainLoop.getAvg();
    qDebug() << "Getstates: " << gst.getAvg();
    qDebug() << "transfer: " << trn.getAvg();
    qDebug() << "add states: " << addst.getAvg();
    qDebug() << "Set next st: " << stnxt.getAvg();
    /*
     *  Avg beforeloop;
    Avg clone;
    Avg slide;
    Avg stateparam;
    Avg checkchecked;
    Avg push;
     */
    qDebug() << "beforlup: " << beforeloop.getAvg();
    qDebug() << "clone: " << clone.getAvg();
    qDebug() << "slide: " << slide.getAvg();
    qDebug() << "stateparam: " << stateparam.getAvg();
    qDebug() << "push: " << push.getAvg();
    qDebug() << "all: " << all.getAvg();
    qDebug() << "inner loop: " << innerLoop.getAvg();
    qDebug() << "calc prior: " << calcPrior.getAvg();
}
#endif

void PuzzleSolver::solve()
{
    if (!boardToSolve)
        return;

    newSearch();
    this->statesChecked = 0;
    while (!isSolved())
    {

        this->statesChecked++;

        auto states = getAvailableStates(getCurrentState());

        stateManager->transferToClosedList(stateManager->getCurrentStateIterator());

        for (u_int i = 0; i<states->size(); i++)
        {
            stateManager->addState((*states)[i]);
        }

        stateManager->setNextCurrentState();

        if (statesChecked > stateCheckLimit) {
            stringstream s;
            s << "Over " << stateCheckLimit << " states checked.";
            throw Exception(s.str().c_str());
        }
    }

#ifdef MY_DEBUG
    debugPrint();
#endif


}

void PuzzleSolver::setBoardToSolve(PuzzleBoard &b)
{
    boardToSolve = std::shared_ptr<board::PuzzleBoard>(b.clone());
    setGoalBoard();
}


const std::vector<board::SLIDE_DIRECTIONS> PuzzleSolver::getResult()
{
    if (boardToSolve == 0){
        std::vector<board::SLIDE_DIRECTIONS> a;
        return a;
    }

    if (steps->size() == 0)
    {
        recursiveAddSteps(getCurrentState());
        std::reverse(steps->begin(), steps->end());

    }
    return *steps;
}

const std::shared_ptr<PuzzleBoardState> PuzzleSolver::getCurrentState()
{
    std::shared_ptr<PuzzleBoardState> result(0);

    auto it = stateManager->getCurrentStateIterator();
    if (stateManager->openStateList.end() != it)
        result = (*it).second;


    return result;
}

const StateVectorPtr PuzzleSolver::getAvailableStates(const shared_ptr<PuzzleBoardState> &stateToCheck)
{
#ifdef MY_DEBUG
    all.start();
    beforeloop.start();
#endif
    StateVectorPtr states = std::make_shared< vector< shared_ptr<PuzzleBoardState> > >();
    auto currentBoard = stateToCheck->currentBoard;

    const u_int moveCount = stateToCheck->movesMadeSoFar +1;
#ifdef MY_DEBUG
    beforeloop.stop();
    innerLoop.start();
#endif
    for (u_int i=0; i<PuzzleBoard::directions.size(); i++)
    {
#ifdef MY_DEBUG
        clone.start();
#endif
        auto tmpBoard = currentBoard->clone();
#ifdef MY_DEBUG
        clone.stop();
        slide.start();
#endif
        const bool &slided = tmpBoard->slidePuzzle(PuzzleBoard::directions[i]);
#ifdef MY_DEBUG
        slide.stop();
#endif
        if (slided)
        {
#ifdef MY_DEBUG
            stateparam.start();
#endif
            std::shared_ptr<board::SLIDE_DIRECTIONS> dptr = make_shared<board::SLIDE_DIRECTIONS>(PuzzleBoard::directions[i]);
#ifdef MY_DEBUG
            calcPrior.start();
#endif
            const  auto &prior = calculatePriority(*tmpBoard,moveCount);
#ifdef MY_DEBUG
            calcPrior.stop();
#endif

            PuzzleBoardStateParams p(getCurrentState(),tmpBoard,moveCount,prior,dptr);
#ifdef MY_DEBUG
            stateparam.stop();
#endif

            std::shared_ptr<PuzzleBoardState> tmp = make_shared<PuzzleBoardState>(p);
#ifdef MY_DEBUG
            checkchecked.start();
#endif
            const  bool &checked = stateManager->hasThisStateBeenChecked(tmp);

#ifdef MY_DEBUG
            checkchecked.stop();
#endif
            if (checked)
                continue;
#ifdef MY_DEBUG
            push.start();
#endif

            states->push_back(tmp);
#ifdef MY_DEBUG
            push.stop();
#endif
        }
    }
#ifdef MY_DEBUG
    innerLoop.stop();
    all.stop();
#endif
    return states;
}

void PuzzleSolver::setGoalBoard()
{
    auto b = boardToSolve->clone();
    b->setCorrectAlignment();
    goalBoard = std::shared_ptr<board::PuzzleBoard>(b);
}

bool PuzzleSolver::isSolved()
{
    if (isSolved(*(getCurrentState())))
        return true;
    return false;
}

bool PuzzleSolver::isSolved(const PuzzleBoardState &p)
{
    if (*(p.currentBoard) == *goalBoard)
        return true;
    return false;
}

void PuzzleSolver::recursiveAddSteps(std::shared_ptr<PuzzleBoardState> parent)
{

    if (parent->directionToThisState != 0)
    {
        steps->push_back(*parent->directionToThisState);
        if (parent->cameFrom !=0)
        {
            recursiveAddSteps(parent->cameFrom);
        }
    }

}

void StateManager::setNextCurrentState()
{
    auto s = getStateWithLowestPriority();
    currentStateIt = s;
    //    openStateList.erase(s);

}

bool StateManager::isEmptyCurrent()
{
    if (currentStateIt == openStateList.end())
        return true;
    return false;
}

const StateListIterator StateManager::getCurrentStateIterator()
{
    return currentStateIt;
}

u_int StateManager::getNumStates()
{
    return openStateList.size();
}

bool StateManager::hasThisStateBeenChecked(shared_ptr<PuzzleBoardState> &state)
{
    auto board = state->currentBoard;

    for(auto it = closedList.begin(); it!= closedList.end(); ++it)
    {
        auto tmpBoard = (*it)->currentBoard;
        if (*tmpBoard == *board)
            return true;
    }

    return false;
}

void StateManager::transferToClosedList(StateListIterator state)
{
    if (state == openStateList.end())
        return;

    closedList.insert(state->second);
    openStateList.erase(state);
}

StateListIterator StateManager::getStateWithLowestPriority()
{
    auto it = openStateList.begin();
    return it;
}

void StateManager::clear()
{
    openStateList.clear();
    closedList.clear();
    currentStateIt = openStateList.begin();
}


PuzzleBoardState::~PuzzleBoardState()
{
}


PuzzleBoardState::PuzzleBoardState(const PuzzleBoardStateParams &params):
    cameFrom(params.cameFrom),
    currentBoard(params.currentBoard),
    movesMadeSoFar(params.movesMadeSoFar),
    priority(params.priority),
    directionToThisState(params.directionToThisState)

{

}


StateManager::StateManager():
    currentStateIt(0)
{
}

void StateManager::addState(std::shared_ptr<PuzzleBoardState> s)
{
    openStateList.insert(std::pair<u_int,shared_ptr<PuzzleBoardState>>(s->priority,s));
}

StateManager::~StateManager()
{
}

u_int StateManager::getOpenStateSize() const
{
    return openStateList.size();
}

u_int StateManager::getClosedStateSize() const
{
    return closedList.size();
}

u_int PuzzleSolver::getStatesChecked() const
{
    return statesChecked;
}





void PuzzleSolver::setStateCheckLimit(const u_int &value)
{
    stateCheckLimit = value;
}

int PuzzleSolver::calculatePriority(PuzzleBoard &b, const int &moveCount)
{
    switch(priorityFunction)
    {
    case HAMMING:
        return b.calculateHammingPriority(moveCount);
    case MANHATTAN:
        return b.calculateManhattanPriority(moveCount);
    }
    return 0;
}



PuzzleBoardStateParams::PuzzleBoardStateParams():
    cameFrom(0),
    currentBoard(0),
    movesMadeSoFar(0),
    priority(0),
    directionToThisState(0)
{
}

PuzzleBoardStateParams::PuzzleBoardStateParams( std::shared_ptr<PuzzleBoardState> cameFrom,
                                                std::shared_ptr<board::PuzzleBoard> currentBoard,
                                                u_int movesMadeSoFar,
                                                u_int priority,
                                                std::shared_ptr<board::SLIDE_DIRECTIONS> directionToThisState):
    cameFrom(cameFrom),currentBoard(currentBoard),movesMadeSoFar(movesMadeSoFar),priority(priority),directionToThisState(directionToThisState)
{
}


void PuzzleSolver::setPriorityFunction(const PriorityFunction &value)
{
    priorityFunction = value;
}

