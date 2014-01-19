#include "gui/include/puzzlesolverstartscreen.h"
#include "ui_puzzlesolverstartscreen.h"

PuzzleSolverStartScreen::PuzzleSolverStartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PuzzleSolverStartScreen)
{
    ui->setupUi(this);
}

PuzzleSolverStartScreen::~PuzzleSolverStartScreen()
{
    delete ui;
}
