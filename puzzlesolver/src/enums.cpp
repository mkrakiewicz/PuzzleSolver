#include "enums.h"

using namespace board;

namespace board {

SLIDE_DIRECTIONS operator-(const SLIDE_DIRECTIONS& d)
{
    SLIDE_DIRECTIONS r;
    switch(d)
    {
        case UP: return r=DOWN;
        case DOWN: return r=UP;
        case LEFT: return r=RIGHT;
        case RIGHT: return r=LEFT;
    }
    return UP;
}

std::string dirToStr(SLIDE_DIRECTIONS direction)
{
    std::string s;
    switch (direction)
    {
        case UP:
        s="UP";
        break;
        case DOWN:
        s="DOWN";
        break;
        case LEFT:
        s="LEFT";
        break;
        case RIGHT:
        s="RIGHT";
    }
    return s;
}

}
