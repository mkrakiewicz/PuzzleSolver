#include "stdafx.h"

#include <QThread>
#include "puzzlesolverstartscreen.h"
#include "ui_puzzlesolverstartscreen.h"
#include "puzzleboard.h"

using namespace board;

PuzzleSolverStartScreen::PuzzleSolverStartScreen(QWidget *parent) :
    QMainWindow(parent),
    boardSize(new Dimension2D),
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

    boardSize->horizontalSize = x;


}

void PuzzleSolverStartScreen::on_verticalBoardSizeSlider_valueChanged(int value)
{
    auto x = ui->horizontalBoardSizeSlider->value();
    auto y = value;
    ui->labelBoardSize->setText(QString::number(x) + " x " + QString::number(y));

    boardSize->verticalSize = y;

}

void PuzzleSolverStartScreen::on_pushButton_clicked()
{
    for (int i =0; i<200; i++)
    {
        auto g = ui->dial->geometry();
        g.translate(1,0);
        ui->dial->setGeometry(g);
        QThread::msleep (20);
    }
}
