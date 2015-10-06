#include "accountcreate.h"
#include "ui_accountcreate.h"

accountCreate::accountCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountCreate)
{
    ui->setupUi(this);
}

accountCreate::~accountCreate()
{
    delete ui;
}
