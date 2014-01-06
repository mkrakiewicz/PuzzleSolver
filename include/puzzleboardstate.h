#ifndef PUZZLEBOARDSTATE_H
#define PUZZLEBOARDSTATE_H

#include "puzzlestate.h"
#include "exceptions.h"
#include <vector>
#include <sstream>


class TwoDimensions
{
public:
    TwoDimensions(int sizeX, int sizeY);

    inline int getHorizontalSize() const
    {

        return sizeX;
    }

    inline int getVerticalSize() const
    {
        return sizeY;
    }
    virtual ~TwoDimensions(){}


protected:
    const unsigned int sizeX, sizeY;
};

template <class T>
class TwoDimensionalStateContainer : public TwoDimensions {
public:
    TwoDimensionalStateContainer(int sizeX,int sizeY) :
        TwoDimensions(sizeX, sizeY)
    {
        if (sizeX <= 0 || sizeY <= 0 )
            throw new Exception("Container size must be at least 1");
    }

    virtual void setState(PointState<T> pstate) = 0;
    virtual T getStateAt(Point p) = 0;
    virtual ~TwoDimensionalStateContainer(){}
};


template <class T>
class PointStateContainer : public TwoDimensionalStateContainer<T>
{
public:
    PointStateContainer(int sizeX, int sizeY):
        TwoDimensionalStateContainer<T>(sizeX,sizeY),
        states(this->getVerticalSize(), std::vector<T>(this->getHorizontalSize()))
    {

    }

    virtual void setState(PointState<T> pstate) {
        states[pstate.getX()][pstate.getY()] = pstate.state;
    }
    virtual T getStateAt(Point p) {
        return states[p.getX()][p.getY()];
    }

    T getStateAt(unsigned int x, unsigned int y) {
        if (x>=this->sizeX || y>=this->sizeY)
        {
            std::stringstream msg;
            msg << "Requested position " << x << ", " << y << " exceeds State Container Size: " << this->sizeX << ", " << this->sizeY;
            throw Exception(msg.str());
        }
        return getStateAt(Point(x,y));
    }

    void equalizeStates(T value){
        for (int y=0; y<this->getVerticalSize(); y++)
        {
            for (int x=0; x<this->getHorizontalSize(); x++)
            {
                PointState<T> p(x,y,value);
                setState(p);
            }
        }
    }

    virtual ~PointStateContainer(){}

private:
    std::vector< std::vector<T> > states; //Two dimensional vector
};

typedef PointStateContainer<int> NumericPointStateContainer;

template <class T>
class PuzzleBoardState : public PointStateContainer<T>
{
public:
    PuzzleBoardState(int sizeX,int sizeY):
        PointStateContainer<T>(sizeX, sizeY)
    {

    }

    virtual ~PuzzleBoardState(){}
};

typedef  PuzzleBoardState<int> NumericPuzzleBoardState;

#endif // PUZZLEBOARDSTATE_H
