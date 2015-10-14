#include "managerlogin.h"
#include "ui_managerlogin.h"
#include "customerlog.h"
#include "openaccount.h"

extern struct Helper::currentClientInfo client;
managerLogin::managerLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managerLogin)
{
    ui->setupUi(this);

    customerLog CL;
    MainWindow mw;
    mw.connOpen();
    QSqlQuery qry,qry2,qry3;
    qry.prepare("Select * from CLIENT_REQUEST where done=0");
    if(qry.exec()){
        while(qry.next()){
            QMessageBox msgBox;
            msgBox.setText("Account Request By '"+qry.value(0).toString()+"'");

            if(qry.value(1).toInt() == 0 && qry.value(2).toInt() == 1){
                qry2.prepare("UPDATE BANKING_CREDENTIALS SET CheqAcct = 1, SavAcct = 1 WHERE name ='"+qry.value(0).toString()+"'");
                QString date = QString::fromStdString(CL.now());
                qry3.prepare("UPDATE CLIENT_REQUEST SET done=1, date='"+date+"' WHERE name='"+qry.value(0).toString()+"'");
                msgBox.setInformativeText("Client wants to open a chequing account");
            }else{
                qry2.prepare("UPDATE BANKING_CREDENTIALS SET SavAcct = 1 WHERE name ='"+qry.value(0).toString()+"'");
                QString date = QString::fromStdString(CL.now());
                qDebug()<<(date);
                qry3.prepare("UPDATE CLIENT_REQUEST SET done=1, date='"+date+"' WHERE name='"+qry.value(0).toString()+"'");
                msgBox.setInformativeText("Client wants to open a savings account");
            }
            QPushButton *Accept = msgBox.addButton(tr("Open"), QMessageBox::ActionRole);
            QPushButton *Decline = msgBox.addButton(tr("Don't Open"),QMessageBox::ActionRole);
            QPushButton *cancel = msgBox.addButton(tr("Cancel"),QMessageBox::ActionRole);
            msgBox.exec();

            if(msgBox.clickedButton() == Accept){
                if(qry2.exec() && qry3.exec()){
                    QMessageBox::information(this,"Done","Account Created");
                    qDebug()<<(qry2.lastQuery());
                    qDebug()<<(qry3.lastQuery());
                }else{
                    qDebug()<<(qry2.lastQuery());
                    qDebug()<<(qry3.lastError());
                }

            }else{
                QMessageBox::information(this,"Declined","Account NOT Created");

            }
        }
    }


}

managerLogin::~managerLogin()
{
    delete ui;
}

void managerLogin::on_createAcc_clicked() //Go to create an account for an existing user
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

void managerLogin::on_pushButton_4_clicked() //Logout, exit to Login screen
{
    MainWindow mw;
    this->hide();
    mw.show();


}

void managerLogin::on_pushButton_clicked() //Create an account for an existing user
{
    this->hide();
    OpenAccount OA;
    OA.setModal(true);
    OA.exec();
}

void managerLogin::on_pushButton_3_clicked()
{
    /*OBTAIN AGGREGATE DATA ON BANK*/

}
