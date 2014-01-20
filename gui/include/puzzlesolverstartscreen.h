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

class PuzzleSolverStartScreen : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PuzzleSolverStartScreen(QWidget *parent = 0);
    ~PuzzleSolverStartScreen();
    

protected:
    std::shared_ptr<board::Dimension2D> boardSize;
private slots:
    void on_horizontalBoardSizeSlider_valueChanged(int value);

    void on_verticalBoardSizeSlider_valueChanged(int value);

    void on_pushButton_clicked();

private:
    Ui::PuzzleSolverStartScreen *ui;
};

#endif // PUZZLESOLVERSTARTSCREEN_H
