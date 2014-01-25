#ifndef PUZZLESOLVERSTARTSCREEN_H
#define PUZZLESOLVERSTARTSCREEN_H

#include <QMainWindow>
#include <memory>
#include "enums.h"


namespace Ui {
    class PuzzleSolverStartScreen;
}

namespace board {
    class Dimension2D;
}

class QPuzzleBoard;
class QLabelPuzzle;
class Position2D;
class QSolutionAnimator;
class AboutDialog;

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
    void updateSolutionGUI();
    void setSolutionStepsToGUI(const std::vector<board::SLIDE_DIRECTIONS> &r);
    void setSolutionStatstoGUI(const std::vector<board::SLIDE_DIRECTIONS> &r);
private slots:
    void on_horizontalBoardSizeSlider_valueChanged(int value);

    void on_verticalBoardSizeSlider_valueChanged(int value);

    void on_buttonSolvePuzzle_clicked();

    void on_buttonCreateNewBoard_clicked();

    void on_actionExit_triggered();

    void on_buttonAnimateSteps_clicked();

    void on_actionAuthor_triggered();

private:
    Ui::PuzzleSolverStartScreen *ui;
    std::shared_ptr < std::map<u_int,QLabelPuzzle* > > puzzles;
    QPuzzleBoard* board;
    std::shared_ptr <QSolutionAnimator> animator;

    bool solutionViewed = false;
    AboutDialog *aboutDialog;

};

#endif // PUZZLESOLVERSTARTSCREEN_H
