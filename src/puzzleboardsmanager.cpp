#include "puzzleboardsmanager.h"

using namespace std;

NumericPuzzleBoardsManager::NumericPuzzleBoardsManager(const Dimension2D &d):
    PuzzleBoardsManager<NumericPuzzle>(d)
{
}

NumericPuzzleBoard NumericPuzzleBoardsManager::getEmptyBoard()
{

    NumericPuzzleBoardContainer c(getDimensions());

    for (u_int x = 0; x<c.horizontalSize; x++ )
    {
            for (u_int y = 0; y<c.verticalSize; y++ )
            {
                c.setPuzzle(shared_ptr<Position2D> (points[Position2D(x,y)]), shared_ptr<NumericPuzzle> (new NumericPuzzle(0)));
            }
    }

    return NumericPuzzleBoard(c.getDimensions(),c);

}
