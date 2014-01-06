#ifndef POSITION2D_H
#define POSITION2D_H

#include "puzzleboard.h"


class Position2D
{
public:
    Position2D(int x,int y);
    const int X,Y;

    bool positionExceedsBounds(const Dimension2D &);

};


#endif // POSITION2D_Hh
