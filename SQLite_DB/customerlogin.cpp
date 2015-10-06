#include "customerlogin.h"
#include "ui_customerlogin.h"
#include "mainwindow.h"

using namespace std;
customerlogin::customerlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customerlogin)
{
    ui->setupUi(this);
}

customerlogin::~customerlogin()
{
    delete ui;
}

void customerlogin::on_pushButton_clicked()
{
//    MainWindow db;

//    QString name = ui->lineEdit->text();
//    db.connOpen();

//    QSqlQuery qry;
//    qry.prepare("INSERT INTO BANKING_CREDENTIALS (Name) VALUES ('"+name+"')");

//    if(qry.exec()){
//       QMessageBox::critical(this,tr("Save"),tr("Saved"));
//       db.connClose();
//    }
//    else{
//       QMessageBox::critical(this,tr("ERROR ON INSERT"),qry.lastError().text());
//    }
}
