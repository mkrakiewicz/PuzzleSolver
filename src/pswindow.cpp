#include "pswindow.h"
#include "ui_pswindow.h"

PSWindow::PSWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PSWindow)
{
    ui->setupUi(this);
}

PSWindow::~PSWindow()
{
    delete ui;
}
