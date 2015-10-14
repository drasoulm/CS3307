#include "bankdata.h"
#include "ui_bankdata.h"

BankData::BankData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BankData)
{
    ui->setupUi(this);
}

BankData::~BankData()
{
    delete ui;
}
