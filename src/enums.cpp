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

}
