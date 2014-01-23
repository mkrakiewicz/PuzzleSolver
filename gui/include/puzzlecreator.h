#ifndef PUZZLECREATOR_H
#define PUZZLECREATOR_H

class QLabelPuzzle;
class QWidget;
class QPuzzleBoard;

class PuzzleCreator
{
public:
    PuzzleCreator();
    u_int moveBy, puzzleSize, xOffsetMultiplier, yOffsetMultiplier;
    QPuzzleBoard* parentBoard;
    QWidget *parentObject;

    QLabelPuzzle *createPuzzle(u_int ID);
};

#endif // PUZZLECREATOR_H
