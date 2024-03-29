#include "errordialog.h"
#include "ui_errordialog.h"

void ErrorDialog::setMessage(const QString &a)
{
    ui->labelMessage->setText(a);
}

void ErrorDialog::retranslateEverything()
{
    ui->retranslateUi(this);
}

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);

}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}
