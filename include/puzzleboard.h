#ifndef PUZZLEBOARDSTATE_H
#define PUZZLEBOARDSTATE_H

#include "puzzle.h"
#include "exceptions.h"
#include <vector>
#include <sstream>
#include <memory>

class Dimension2D
{
public:
    Dimension2D(int sizeX, int sizeY);
    virtual ~Dimension2D(){}

    const unsigned int horizontalSize, verticalSize;
};

template <class T>
class PositionToObjectMapper : public Dimension2D {
public:
    PositionToObjectMapper(const Dimension2D &d) :
        Dimension2D(d)
    {
        if (horizontalSize <= 0 || verticalSize <= 0 )
            throw new Exception("Container size must be at least 1");
    }

    void setAt(std::shared_ptr<Dimension2D> pos, std::shared_ptr<T> object)
    {

    }

    std::shared_ptr<T>  getAt(const Dimension2D &pos)
    {

    }

    virtual ~PositionToObjectMapper(){}
};


/*template <class T>
class PointStateContainer : public PositionToObjectMapper<T>
{
public:
    PointStateContainer(const Dimension2D &d):
        PositionToObjectMapper<T>(d),
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
    PuzzleBoardState(const Dimension2D &d):
        PointStateContainer<T>(d)
    {

    }

    T getPuzzleAt

    virtual ~PuzzleBoardState(){}
};

typedef  PuzzleBoardState<int> NumericPuzzleBoardState;*/

#endif // PUZZLEBOARDSTATE_H
