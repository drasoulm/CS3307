#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customerlog.h"
#include "helper.h"

Helper::currentClientInfo client;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    /*LOGIN*/
    customerLog logFile;
    QString usernameIn, passwordIn;
    usernameIn = ui->lineEdit->text();
    passwordIn = ui->lineEdit_2->text();

    /*Store user input*/
    connOpen();

    QSqlQuery qry;
    qry.prepare("Select * from BANKING_CREDENTIALS where UserName='"+usernameIn+"' and Password='"+passwordIn+"'");

    if(qry.exec()){

        while(qry.next()){
            //Initialize client
            client.manager = qry.value(3).toInt();
            client.name = qry.value(0).toString();
            client.ID = qry.value(1).toString();
            client.savBal = qry.value(5).toDouble();
            client.cheqBal = qry.value(4).toDouble();
            client.passWord = qry.value(2).toDouble();
            client.isTrail = qry.value(8).toInt();
            client.maintPers = qry.value(9).toInt();
        }

        /*Check to see if client is a manager, customer, or maintance role and display correct view*/

        if(client.manager == 1){
            QString role = "MANAGER";
            logFile.addClientToLog(client.name, client.ID, role);
            this->hide();
            managerLogin managerlogin;
            managerlogin.setModal(true);
            managerlogin.exec();
        }
        else if(client.manager == 0 && client.maintPers == 0){
            QString role = "CUSTOMER";
            logFile.addClientToLog(client.name, client.ID, role);

            this->hide();

            clientView customerLogin;
            customerLogin.setModal(true);
            customerLogin.exec();
        }
        else if(client.maintPers == 1){
            QString role = "MAINTANCE";
            logFile.addClientToLog(client.name, client.ID, role);
            this->hide();
            MaintanenceView maintanceLogin;
            maintanceLogin.setModal(true);
            maintanceLogin.exec();
        }
        else {
            ui->label->setText("Incorrect login information, try again");
            //Cases: Username is wrong, password is wrong, both are wrong, and user doesn't exist..
        }
    }
}

void MainWindow::connClose(){
    QSqlDatabase mydb;
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

bool MainWindow::connOpen(){
    QSqlDatabase mydb;
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("database.db");

    if(!mydb.open()){
        qDebug()<<("not connected....");
        return false;
    }else {
        qDebug()<<("connected....");
        return true;
    }
}
bool MainWindow::fileExists(QString path) {
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

void MainWindow::createDBFileThenTable(){
    QFile file("database.db");
     file.open(QIODevice::ReadWrite);
     file.close();
     connOpen();
     QSqlQuery query;
     query.exec("CREATE TABLE 'BANKING_CREDENTIALS' ('Name' TEXT, 'UserName' TEXT, 'Password' TEXT, 'Manager' INT, 'Cheq' DOUBLE, 'Sav' DOUBLE, 'SavAcct' INT, 'CheqAcct' INT)");
     connClose();

}

