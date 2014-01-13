#ifndef POSITION2D_H
#define POSITION2D_H

#include<memory>

namespace board  {

class Dimension2D;

}

class Position2D
{
public:
    Position2D(int x = 0,int y = 0);
    int X,Y;

    bool positionExceedsBounds(const board::Dimension2D &);

    inline bool operator==(const Position2D &toCompare) const
    {
        if (X != toCompare.X)
            return false;
        if (Y != toCompare.Y)
            return false;
        return true;
    }

    inline bool operator !=(const Position2D &toCompare) const
    {
        return !operator ==(toCompare);
    }

    inline bool operator <(const Position2D &toCompare) const
    {
        if ((X < toCompare.X) && (Y < toCompare.Y))
            return true;

        int thisSum = X+Y , otherSum = toCompare.X+toCompare.Y;

        if (thisSum < otherSum)
            return true;

        return false;
    }

    std::shared_ptr<Position2D> clone()
    {
        return std::shared_ptr<Position2D>(new Position2D(*this));
    }

//    inline Position2D& operator=(const Position2D & pos)
//    {
//        *this = Position2D(pos.X,pos.Y);

//        return *this;
//    }

    std::string toString();
};


#endif // POSITION2D_Hh
