#include "puzzlesolverstartscreen.h"
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

void PuzzleSolverStartScreen::on_horizontalBoardSizeSlider_valueChanged(int value)
{
    auto x = value;
    auto y = ui->verticalBoardSizeSlider->value();
    ui->labelBoardSize->setText(QString::number(x) + " x " + QString::number(y));

}

void PuzzleSolverStartScreen::on_verticalBoardSizeSlider_valueChanged(int value)
{
    auto x = ui->horizontalBoardSizeSlider->value();
    auto y = value;
    ui->labelBoardSize->setText(QString::number(x) + " x " + QString::number(y));
}
