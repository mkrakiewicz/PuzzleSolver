#include "stdafx.h"

#include <QThread>
#include <QPropertyAnimation>
#include <QFrame>
#include "puzzlesolverstartscreen.h"
#include "ui_puzzlesolverstartscreen.h"
#include "puzzleboard.h"
#include "position2d.h"
#include "puzzleqobject.h"


#define MAX_BOARD_PIXELS 324
#define BOARD_MARGIN 5


using namespace board;

PuzzleSolverStartScreen::PuzzleSolverStartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PuzzleSolverStartScreen),
    puzzles(new std::map<u_int,std::shared_ptr <QLabelPuzzle> >)

{
    ui->setupUi(this);
}

PuzzleSolverStartScreen::~PuzzleSolverStartScreen()
{
    delete ui;
}

const Position2D &PuzzleSolverStartScreen::positionToPixelPosition(const Position2D &pos)
{
    Position2D startPos = pos;

    startPos.X = ui->framePuzzleContainer->pos().x() + BOARD_MARGIN;
    startPos.Y = ui->framePuzzleContainer->pos().y() + BOARD_MARGIN;
    const Position2D &result = startPos;
    return result;
}

void PuzzleSolverStartScreen::createLabelPuzzles()
{
    puzzles->clear();
    u_int biggerVal = 0;

    auto boardSize = getBoardDimensions();
    const u_int totalPuzzles = (boardSize->verticalSize * boardSize->horizontalSize) - 1;

    if (boardSize->horizontalSize > boardSize->verticalSize)
        biggerVal = boardSize->horizontalSize;
    else
        biggerVal = boardSize->verticalSize;

    const u_int puzzleSize = MAX_BOARD_PIXELS/biggerVal;
    const u_int moveBy = puzzleSize;


//    const QPoint initialPosition(BOARD_MARGIN,BOARD_MARGIN);
    u_int count = 1;
    for (u_int y=0; y<boardSize->verticalSize; y++)
    {
        for (u_int x=0; x<boardSize->horizontalSize; x++)
        {
            if (count == (totalPuzzles + 1))
                break;
            std::shared_ptr <QLabelPuzzle> p ( new QLabelPuzzle(this));
            p->ID = count;
            p->setText(QString::number(p->ID));
            QRect tmp = p->geometry();
            tmp.setWidth(puzzleSize);
            tmp.setHeight(puzzleSize);
            p->setGeometry(tmp);
//            p->setProperty()
            p->move(5+x*moveBy,5+y*moveBy);
            p->setFrameShape(QFrame::Shape::Panel);
            p->show();
            p->setParent(ui->framePuzzleContainer);
            p->setAlignment(Qt::AlignCenter);
            (*puzzles)[count] = p;

            count++;
        }
    }

}

const std::shared_ptr<Dimension2D> PuzzleSolverStartScreen::getBoardDimensions()
{
    std::shared_ptr<Dimension2D> result ( new Dimension2D(ui->horizontalBoardSizeSlider->value(),ui->verticalBoardSizeSlider->value()));
    return result;
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

void PuzzleSolverStartScreen::on_pushButton_clicked()
{

//    QPropertyAnimation *animation = new QPropertyAnimation(ui->dial, "geometry");
//    animation->setDuration(1000);
//    animation->setStartValue(QRect(0, 0, 100, 30));
//    animation->setEndValue(QRect(250, 250, 100, 30));

//    animation->start();

}

void PuzzleSolverStartScreen::on_pushButton_2_clicked()
{
    createLabelPuzzles();
}
