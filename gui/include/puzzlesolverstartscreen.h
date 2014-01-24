#ifndef PUZZLESOLVERSTARTSCREEN_H
#define PUZZLESOLVERSTARTSCREEN_H

#include <QMainWindow>
#include <memory>

namespace Ui {
    class PuzzleSolverStartScreen;
}

namespace board {
    class Dimension2D;
}

class QPuzzleBoard;
class QLabelPuzzle;
class Position2D;

class PuzzleSolverStartScreen : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PuzzleSolverStartScreen(QWidget *parent = 0);
    ~PuzzleSolverStartScreen();
    

protected:
//    std::shared_ptr<QLabelPuzzle>
    const Position2D& positionToPixelPosition(const Position2D& pos);
    void createLabelPuzzles();
    const std::shared_ptr<board::Dimension2D> getBoardDimensions();
private slots:
    void on_horizontalBoardSizeSlider_valueChanged(int value);

    void on_verticalBoardSizeSlider_valueChanged(int value);

    void on_buttonSolvePuzzle_clicked();

    void on_buttonCreateNewBoard_clicked();

    void on_actionExit_triggered();

private:
    Ui::PuzzleSolverStartScreen *ui;
    std::shared_ptr < std::map<u_int,QLabelPuzzle* > > puzzles;
    QPuzzleBoard* board;

};

#endif // PUZZLESOLVERSTARTSCREEN_H
