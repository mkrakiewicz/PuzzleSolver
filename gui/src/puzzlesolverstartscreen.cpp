#include "stdafx.h"

#include <QThread>
#include <QString>
#include <QPropertyAnimation>
#include <QFrame>
#include <QSequentialAnimationGroup>
#include "puzzlesolverstartscreen.h"
#include "config.h"
#include "ui_puzzlesolverstartscreen.h"
#include "puzzleboard.h"
#include "position2d.h"
#include "qpuzzle.h"
#include "qpuzzlecreator.h"
#include "qpuzzleboard.h"
#include "puzzlesolver.h"
#include "qsolutionanimator.h"
#include "exceptions.h"
#include "aboutdialog.h"
#include "errordialog.h"


using namespace board;

PuzzleSolverStartScreen::PuzzleSolverStartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PuzzleSolverStartScreen),
    puzzles(new std::map<u_int,QLabelPuzzle* >),
    board(0),
    animator(0),
    aboutDialog(0),
    errorDialog(0)

{
    ui->setupUi(this);
    board = new QPuzzleBoard(this,*(this->getBoardDimensions()));
    ui->tabsMainWindow->setCurrentIndex(0);
    ui->buttonAnimateSteps->setDisabled(true);
    ui->tabsMainWindow->setTabEnabled(1,false);

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

void PuzzleSolverStartScreen::createNewBoard()
{
    puzzles->clear();
    auto boardSize = getBoardDimensions();
    board->deleteInnerObjects();
    if (board != 0) {
        delete board;
    }
    board = new QPuzzleBoard(this,*(boardSize));
    u_int biggerVal = 0;
    const u_int totalPuzzles = (boardSize->verticalSize * boardSize->horizontalSize) - 1;

    if (boardSize->horizontalSize > boardSize->verticalSize)
        biggerVal = boardSize->horizontalSize;
    else
        biggerVal = boardSize->verticalSize;

    const u_int puzzleSize = MAX_BOARD_PIXELS/biggerVal;
    const u_int moveBy = puzzleSize;
    QPuzzleCreator pC;
    pC.moveBy = moveBy;
    pC.parentObject = ui->framePuzzleContainer;
    pC.puzzleSize = puzzleSize;
    pC.parentBoard = board;
    pC.realBoard = board->getInnerBoard();

    //    const QPoint initialPosition(BOARD_MARGIN,BOARD_MARGIN);
    u_int count = 1;
    for (u_int y=0; y<boardSize->verticalSize; y++)
    {
        for (u_int x=0; x<boardSize->horizontalSize; x++)
        {
            if (count == (totalPuzzles + 1))
                break;

            pC.xOffsetMultiplier = x;
            pC.yOffsetMultiplier = y;

            auto p = pC.createPuzzle(count);
            board->setObjectForPuzzle(p);
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

void PuzzleSolverStartScreen::updateSolutionGUI()
{
    auto r = board->solver->getResult();
    if (r.size() > 0)
    {
        ui->buttonAnimateSteps->setEnabled(true);
        setSolutionStepsToGUI(r);
        setSolutionStatstoGUI(r);
    }
}

void PuzzleSolverStartScreen::setSolutionStepsToGUI(const std::vector<board::SLIDE_DIRECTIONS> &r)
{
    for (u_int i=0; i<r.size(); i++)
    {
        QListWidgetItem* l = new QListWidgetItem(QString::fromStdString(dirToStr(r[i])));
        ui->listSolutionSteps->addItem(l);
    }
}

void PuzzleSolverStartScreen::setSolutionStatstoGUI(const std::vector<board::SLIDE_DIRECTIONS> &r)
{
    ui->labelSteps->setText(QString::number(r.size()));

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

void PuzzleSolverStartScreen::solutionFoundAction()
{
    solutionViewed = false;
    ui->suck->setText("success");
    updateSolutionGUI();
}

void PuzzleSolverStartScreen::showErrorDialog(const Exception &e)
{
    if (errorDialog == 0)
    {
        errorDialog = new ErrorDialog(this);
        errorDialog->setFixedSize(errorDialog->size());
    }
    errorDialog->setMessage(e.what());
    errorDialog->show();
}

void PuzzleSolverStartScreen::on_buttonSolvePuzzle_clicked()
{
    ui->labelSteps->setText("");
    ui->listSolutionSteps->clear();
    bool result = false;

    try{
        result = board->solveBoard();
    }catch(const Exception &e)
    {
        showErrorDialog(e);
    }

    if (result){
        solutionFoundAction();
    }
    else
        ui->suck->setText("fail");


}

void PuzzleSolverStartScreen::on_buttonCreateNewBoard_clicked()
{
    createNewBoard();
    ui->tabsMainWindow->setCurrentIndex(1);
    ui->buttonAnimateSteps->setDisabled(true);
    ui->tabsMainWindow->setTabEnabled(1,true);

}

void PuzzleSolverStartScreen::on_actionExit_triggered()
{
    exit(0);
}

void PuzzleSolverStartScreen::on_buttonAnimateSteps_clicked()
{
    if (solutionViewed)
        return;
    solutionViewed = true;
    ui->buttonAnimateSteps->setDisabled(true);
    animator = std::shared_ptr<QSolutionAnimator>(new QSolutionAnimator(this));
    auto solution = board->solver->getResult();
    animator->setSteps(solution);
    animator->setBoardToAnimate(board);
    animator->start();
    //       g.start();1
}

void PuzzleSolverStartScreen::on_actionAuthor_triggered()
{
    if (aboutDialog == 0) {
        aboutDialog = new AboutDialog(this);
        aboutDialog->setFixedSize(aboutDialog->size());

    }
    aboutDialog->show();
}
