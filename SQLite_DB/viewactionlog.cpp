#include "viewactionlog.h"
#include "ui_viewactionlog.h"
#include "QFile"
#include "QTextStream"
#include "maintanenceview.h"

ViewActionLog::ViewActionLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewActionLog)
{
    ui->setupUi(this);

    QFile file("action.log"); //Display Log file
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    ui->textBrowser->setText(stream.readAll());
}

ViewActionLog::~ViewActionLog()
{
    delete ui;
}

void ViewActionLog::on_pushButton_clicked() //Go Back to Maintanence Dash
{
    this->hide();
    MaintanenceView maintanenceV;
    maintanenceV.setModal(true);
    maintanenceV.exec();
}
