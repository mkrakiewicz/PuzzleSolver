#ifndef PUZZLESTATE_H
#define PUZZLESTATE_H

class Point
{
public:
    Point(int x,int y);
    void setNewPosition(Point p);
protected:
    int x,y;
};

template <class T>
class PointState
{
public:
    PointState(Point p):
        Point(p)
    {

    }
    void setNewState(T state)
    {
        this->state = state;
    }

protected:
    T state;
};

typedef PointState<int> NumericPointState;

#endif // PUZZLESTATE_H
