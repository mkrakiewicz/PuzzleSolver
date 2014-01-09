#ifndef POSITION2D_H
#define POSITION2D_H

#include<memory>

namespace boards  {

class Dimension2D;

}

class Position2D
{
public:
    Position2D(int x,int y);
    const int X,Y;

    bool positionExceedsBounds(const boards::Dimension2D &);

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
        if (X > toCompare.X)
            return false;
        if (Y > toCompare.Y)
            return false;
        return true;
    }

    std::shared_ptr<Position2D> clone()
    {
        return std::shared_ptr<Position2D>(new Position2D(*this));
    }
};


#endif // POSITION2D_Hh
