#include "managerlogin.h"
#include "ui_managerlogin.h"
#include "customerlog.h"

managerLogin::managerLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managerLogin)
{
    ui->setupUi(this);


}

managerLogin::~managerLogin()
{
    delete ui;
}

void managerLogin::on_createAcc_clicked()
{
    this->hide();

    createuser createuser;
    createuser.setModal(true);
    createuser.exec();

}

void managerLogin::on_pushButton_2_clicked()
{
    this->hide();

    DeleteUser deleteuser;
    deleteuser.setModal(true);
    deleteuser.exec();
}
