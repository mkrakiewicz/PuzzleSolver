#ifndef PUZZLEBOARDSTATE_H
#define PUZZLEBOARDSTATE_H

#include "puzzlestate.h"
#include <vector>

using namespace std;

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


private:
    int sizeX, sizeY;
};

template <class T>
class TwoDimensionalStateContainer : public TwoDimensions {
public:
    TwoDimensionalStateContainer(int sizeX,int sizeY) :
        TwoDimensions(sizeX, sizeY)
    {

    }

    virtual void setState(PointState<T> pstate) = 0;
    virtual T getStateAt(Point p) = 0;
};


template <typename T>
class TwoDimensionalVector : public vector< vector<T> > {};

template <class T>
class PointStateContainer : public TwoDimensionalStateContainer<T>
{
public:
    PointStateContainer(int sizeX, int sizeY):
        TwoDimensionalStateContainer<T>(sizeX,sizeY),
        states(TwoDimensionalVector<T>(this->getVerticalSize(), vector<T>(this->getHorizontalSize())))
    {

    }

    virtual void setState(PointState<T> pstate) {
        states[pstate.getX()][pstate.getY()] = pstate.state;
    }
    virtual T getStateAt(Point p) {
        return states[p.getX()][p.getY()];
    }

    T getStateAt(int x, int y) {
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

private:
    TwoDimensionalVector<T> states;
};

typedef PointStateContainer<int> NumericPointStateContainer;

#endif // PUZZLEBOARDSTATE_H
