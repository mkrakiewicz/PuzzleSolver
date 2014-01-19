#ifndef POSITION2D_H
#define POSITION2D_H

#include <memory>

class Position2D
{
public:
    Position2D(int x = 0,int y = 0);

    int X,Y;

    bool operator==(const Position2D &toCompare) const;
    bool operator!=(const Position2D &toCompare) const;
    bool operator <(const Position2D &toCompare) const;


    std::shared_ptr<Position2D> clone() const;
    std::string toString();
};


#endif // POSITION2D_Hh
