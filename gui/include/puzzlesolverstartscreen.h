#ifndef PUZZLESOLVERSTARTSCREEN_H
#define PUZZLESOLVERSTARTSCREEN_H

#include <QMainWindow>

namespace Ui {
class PuzzleSolverStartScreen;
}

class PuzzleSolverStartScreen : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PuzzleSolverStartScreen(QWidget *parent = 0);
    ~PuzzleSolverStartScreen();
    
private slots:
    void on_horizontalBoardSizeSlider_valueChanged(int value);

    void on_verticalBoardSizeSlider_valueChanged(int value);

private:
    Ui::PuzzleSolverStartScreen *ui;
};

#endif // PUZZLESOLVERSTARTSCREEN_H
