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
    
private:
    Ui::PuzzleSolverStartScreen *ui;
};

#endif // PUZZLESOLVERSTARTSCREEN_H
