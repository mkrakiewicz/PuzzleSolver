#include "puzzleboardsmanager.h"


NumericPuzzleBoardsManager::NumericPuzzleBoardsManager(const Dimension2D &d):
    PuzzleBoardsManager<NumericPuzzle>(d)
{
}

NumericPuzzleBoard NumericPuzzleBoardsManager::getEmptyBoard()
{
    const Dimension2D dim(sizeX,sizeY);
    NumericPuzzleBoardContainer c(dim);

    for (u_int x = 0; x<sizeX; x++ ){
            for (u_int y = 0; y<sizeY; y++ ){
                c.setPuzzle(shared_ptr<Position2D> (points[Position2D(x,y)]), shared_ptr<NumericPuzzle> (new NumericPuzzle(0)));
            }
    }

}
