#ifndef ENUMS_H
#define ENUMS_H

namespace board {
enum SLIDE_DIRECTIONS
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

SLIDE_DIRECTIONS operator-(const SLIDE_DIRECTIONS& d);


}

#endif // ENUMS_H
