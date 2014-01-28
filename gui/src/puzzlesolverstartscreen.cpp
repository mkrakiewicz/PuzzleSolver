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
#include "puzzleshuffler.h"


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
    ui->labelSuccess->setText("success");
    updateSolutionGUI();
}

void PuzzleSolverStartScreen::showErrorDialog(const QString &str)
{
    if (errorDialog == 0)
    {
        errorDialog = new ErrorDialog(this);
        errorDialog->setFixedSize(errorDialog->size());
    }
    errorDialog->setMessage(str);
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
        showErrorDialog(e.what());
    }
    catch(...)
    {
        showErrorDialog("Unknown error?");
    }

    if (result){
        solutionFoundAction();
    }
    else
        ui->labelSuccess->setText("fail");


}

void PuzzleSolverStartScreen::gotoPuzzleBoard()
{
    ui->tabsMainWindow->setCurrentIndex(1);
    ui->buttonAnimateSteps->setDisabled(true);
    ui->tabsMainWindow->setTabEnabled(1,true);
}

void PuzzleSolverStartScreen::on_buttonCreateNewBoard_clicked()
{
    createNewBoard();
    gotoPuzzleBoard();

}

void PuzzleSolverStartScreen::on_actionExit_triggered()
{
    exit(0);
}

void PuzzleSolverStartScreen::createAndStartSlideSequence(const std::vector<board::SLIDE_DIRECTIONS> directions)
{
    animator = std::shared_ptr<QSlideAnimator>(new QSlideAnimator(this));
    animator->setSteps(directions);
    animator->setBoardToAnimate(board);
    animator->start();
}

void PuzzleSolverStartScreen::on_buttonAnimateSteps_clicked()
{
    if (solutionViewed)
        return;
    solutionViewed = true;
    ui->buttonAnimateSteps->setDisabled(true);
    auto moves = board->solver->getResult();
    createAndStartSlideSequence(moves);
}

void PuzzleSolverStartScreen::createAboutDialog()
{
    if (aboutDialog == 0) {
        aboutDialog = new AboutDialog(this);
        aboutDialog->setFixedSize(aboutDialog->size());

    }
}

void PuzzleSolverStartScreen::on_actionAuthor_triggered()
{
    createAboutDialog();
    aboutDialog->show();
}


void PuzzleSolverStartScreen::on_radioShuffleSteps_clicked()
{
    ui->editShuffleStepNum->setEnabled(true);
    ui->editShufflePercentage->setDisabled(true);
}

void PuzzleSolverStartScreen::disablePercentageInput()
{
    ui->editShuffleStepNum->setDisabled(true);
    ui->editShufflePercentage->setEnabled(true);
}

void PuzzleSolverStartScreen::disableStepsInput()
{
    disablePercentageInput();
}

void PuzzleSolverStartScreen::on_radioShufflePercentage_clicked()
{
    disableStepsInput();
}

bool PuzzleSolverStartScreen::isShufflingBySteps()
{
    if (ui->radioShuffleSteps->isChecked()) {
        return true;
    }  return false;
}

int PuzzleSolverStartScreen::getShuffleStepNum()
{
    return ui->editShuffleStepNum->value();
}

double PuzzleSolverStartScreen::getShufflePercentage()
{
    return ui->editShufflePercentage->value();
}

void PuzzleSolverStartScreen::on_buttonShuffle_clicked()
{
    PuzzleShuffler s;
    s.setBoardToShuffle(*(board->getInnerBoard()));

    bool shuffleBySteps = isShufflingBySteps();
    bool shuffleByPercentage = !shuffleBySteps;

    if (shuffleBySteps) {
        s.setShuffleMoves(getShuffleStepNum());
    } else if (shuffleByPercentage)
    {
        getShufflePercentage();
        s.setMinimumShuffledPuzzles(getShufflePercentage());
    }

    try{
        s.shuffle();
    }catch(const Exception &e)
    {
        showErrorDialog(e.what());
    }
    catch(...)
    {
        showErrorDialog("Unknown error w");
    }

    auto moves = s.getStepsOnly();
    createAndStartSlideSequence(*moves);

}
