#ifndef PUZZLEBOARDSTATE_H
#define PUZZLEBOARDSTATE_H

#include "puzzlestate.h"

class TwoDimensions
{
public:
    TwoDimensions(int sizeX, int sizeY);

    int getHorizontalSize() const;
    int getVerticalSize() const;


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
    virtual void getStateAt(Point p) = 0;
};

class PointStateContainer : public TwoDimensionalStateContainer<T>
{
public:
    PointStateContainer(int sizeX, int sizeY);

    virtual void setState(PointState<T> pstate);
    virtual void getStateAt(Point p);
private:
    // Create
    vector< vector<int> > vec(4, vector<int>(4));
    // Write
    vec[2][3] = 10;
    // Read
    int a = vec[2][3];
};

#endif // PUZZLEBOARDSTATE_H
