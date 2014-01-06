#ifndef PUZZLESTATE_H
#define PUZZLESTATE_H

class Point
{
public:
    Point(int x,int y);
    inline int getX()
    {
        return X;
    }
    inline int getY()
    {
        return Y;
    }

private:
    int X,Y;
};

template <class T>
class PointState : public Point
{
public:
    PointState(Point p, T stateValue):
        Point(p), state(stateValue)
    {

    }

    const T state;

protected:

};

typedef PointState<int> NumericPointState;

#endif // PUZZLESTATE_H
