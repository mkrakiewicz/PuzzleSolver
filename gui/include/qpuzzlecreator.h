#ifndef PUZZLECREATOR_H
#define PUZZLECREATOR_H

#include <memory>

class QLabelPuzzle;
class QWidget;
class QPuzzleBoard;

namespace board {
    class IntPuzzleBoard;
}
namespace puzzle {
    class IntPuzzle;
}
class QPuzzleCreator
{
public:
    QPuzzleCreator();
    u_int moveBy, puzzleSize, xOffsetMultiplier, yOffsetMultiplier;
    std::shared_ptr<board::IntPuzzleBoard> realBoard;
    QPuzzleBoard* parentBoard;
    QWidget *parentObject;

    QLabelPuzzle *createPuzzle(const puzzle::IntPuzzle &puzzle);
};

#endif // PUZZLECREATOR_H
