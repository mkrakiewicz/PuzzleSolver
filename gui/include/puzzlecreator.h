#ifndef PUZZLECREATOR_H
#define PUZZLECREATOR_H

class QLabelPuzzle;
class QWidget;

class PuzzleCreator
{
public:
    PuzzleCreator();
    u_int moveBy, puzzleSize, xOffsetMultiplier, yOffsetMultiplier;
    QWidget *parentObject;

    std::shared_ptr <QLabelPuzzle> createPuzzle(u_int ID);
};

#endif // PUZZLECREATOR_H
