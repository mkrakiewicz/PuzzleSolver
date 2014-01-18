#ifndef ENUMS_H
#define ENUMS_H

#include <string>

namespace board
{
    enum SLIDE_DIRECTIONS
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    SLIDE_DIRECTIONS operator-(const SLIDE_DIRECTIONS& d);
    std::string dirToStr(board::SLIDE_DIRECTIONS direction);


}

#endif // ENUMS_H
