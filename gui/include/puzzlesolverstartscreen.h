#ifndef PUZZLESOLVERSTARTSCREEN_H
#define PUZZLESOLVERSTARTSCREEN_H

#include <QMainWindow>
#include <map>
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
class QSlideAnimator;
class AboutDialog;
class ErrorDialog;
class Exception;
class QTranslator;

class PuzzleSolverStartScreen : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PuzzleSolverStartScreen(QWidget *parent = 0);
    ~PuzzleSolverStartScreen();

protected:
    void retranslateEverything();
    int getShuffleStepNum();
    double getShufflePercentage();
    bool isShufflingBySteps();
    void disableStepsInput();
    void disablePercentageInput();
    void gotoPuzzleBoard();
    void createNewBoard();
    void createAboutDialog();
    void createAndStartSlideSequence(const std::vector<board::SLIDE_DIRECTIONS> directions);
    void updateSolutionGUI();
    void setSolutionStepsToGUI(const std::vector<board::SLIDE_DIRECTIONS> &r);
    void setSolutionStatstoGUI(const std::vector<board::SLIDE_DIRECTIONS> &r);
    void solutionFoundAction();
    void showErrorDialog(const QString &str);
    void clearSolutionList();
    const Position2D& positionToPixelPosition(const Position2D& pos);
    const std::shared_ptr<board::Dimension2D> getBoardDimensions();

private slots:
    void on_horizontalBoardSizeSlider_valueChanged(int value);
    void on_verticalBoardSizeSlider_valueChanged(int value);
    void on_buttonSolvePuzzle_clicked();
    void on_buttonCreateNewBoard_clicked();
    void on_actionExit_triggered();
    void on_buttonAnimateSteps_clicked();
    void on_actionAuthor_triggered();
    void on_radioShuffleSteps_clicked();
    void on_radioShufflePercentage_clicked();
    void on_buttonShuffle_clicked();

    void on_actionEnglish_triggered();

    void on_actionPolish_triggered();

private:
    Ui::PuzzleSolverStartScreen *ui;
    std::shared_ptr < std::map<u_int,QLabelPuzzle* > > puzzles;
    QPuzzleBoard* board;
    std::shared_ptr <QSlideAnimator> animator;

    bool solutionViewed = false;
    AboutDialog *aboutDialog;
    ErrorDialog *errorDialog;
    std::shared_ptr<QTranslator> polishTranslator;

};

#endif // PUZZLESOLVERSTARTSCREEN_H
