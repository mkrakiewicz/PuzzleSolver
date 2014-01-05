#ifndef PUZZLEBOARDSTATE_H
#define PUZZLEBOARDSTATE_H

class PuzzleBoardState
{
public:
    PuzzleBoardState(int sizeX, int sizeY);

    int getHorizontalSize() const;
    int getVerticalSize() const;


private:
    int sizeX, sizeY;
};

#endif // PUZZLEBOARDSTATE_H
