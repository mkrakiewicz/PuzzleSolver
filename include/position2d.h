#ifndef POSITION2D_H
#define POSITION2D_H

class Dimension2D;

class Position2D
{
public:
    Position2D(int x,int y);
    const int X,Y;

    bool positionExceedsBounds(const Dimension2D &);

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



};


#endif // POSITION2D_Hh
