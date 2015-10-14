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

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
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
            client.hasCheq = qry.value(7).toInt();
            client.hasSav = qry.value(6).toInt();
            qDebug()<<(qry.record());

        }

        /*Check to see if client is a manager, customer, or maintance role and display correct view*/
        MaintanenceView mv;
        if(client.name=="" && client.passWord =="") {

        ui->label->setText("Incorrect login information, try again"); //Username is wrong, password is wrong, both are wrong, and user doesn't exist..

        }else if(client.manager == 0 && client.maintPers == 0){
        QString action = "MAINWINDOW: CLIENT LOGGED IN";
        QString role = "CLIENT";
        mv.isTrail(client.isTrail, action);
        logFile.addClientToLog(client.name, client.ID, role);

        this->hide();

        clientView customerLogin;
        customerLogin.setModal(true);
        customerLogin.exec();
        }
        else if(client.maintPers == 1){
            QString action = "MAINWINDOW: MAINTANECE LOGGED IN";
            QString role = "MAINTANCE";
            mv.isTrail(client.isTrail, action);
            logFile.addClientToLog(client.name, client.ID, role);
            this->hide();
            MaintanenceView maintanceLogin;
            maintanceLogin.setModal(true);
            maintanceLogin.exec();
        }else if(client.manager == 1){
            QString action = "MAINWINDOW: MANAGER LOGGED IN";
            QString role = "MANAGER";
            mv.isTrail(client.isTrail, action);
            logFile.addClientToLog(client.name, client.ID, role);
            this->hide();
            managerLogin managerlogin;
            managerlogin.setModal(true);
            managerlogin.exec();
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

void MainWindow::createDBFileThenTable(){ //Create Tables, if they don't exist
    QFile file("database.db");
     file.open(QIODevice::ReadWrite);
     file.close();
     connOpen();
     QSqlQuery query;
     query.exec("CREATE TABLE 'BANKING_CREDENTIALS' ('Name' TEXT, 'UserName' TEXT, 'Password' TEXT, 'Manager' INT, 'Cheq' DOUBLE, 'Sav' DOUBLE, 'SavAcct' INT, 'CheqAcct' INT, 'execTrace' INT, 'maintainence' INT)");
     query.exec("INSERT INTO BANKING_CREDENTIALS (Name,UserName,Password,Manager,Cheq,Sav,SavAcct,CheqAcct,execTrace, maintainence) VALUES ('Manager Credentials','ManagerCred','Welcome1234',1,0,0,0,0,1,0)");
     query.exec("INSERT INTO BANKING_CREDENTIALS (Name,UserName,Password,Manager,Cheq,Sav,SavAcct,CheqAcct,execTrace, maintainence) VALUES ('Client Credentials','FirstClient','Welcome1234',0,1,1,5000,5000,1,0)");
     query.exec("INSERT INTO BANKING_CREDENTIALS (Name,UserName,Password,Manager,Cheq,Sav,SavAcct,CheqAcct,execTrace, maintainence) VALUES ('Maintanence Credentials','MantanenceCred','Welcome1234',1,0,0,0,0,1,1)");
     qDebug()<<(query.lastQuery());
     query.exec("CREATE TABLE 'CLIENT_REQUEST' ('name' TEXT, 'openSav' INT, 'openCheq' INT, 'done' INT, 'date' TEXT)");
     connClose();
}

