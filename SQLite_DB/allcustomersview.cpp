#include "allcustomersview.h"
#include "ui_allcustomersview.h"
#include "mainwindow.h"
#include "deleteuser.h"

AllCustomersView::AllCustomersView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllCustomersView)
{

    ui->setupUi(this);

    QSqlQueryModel * model = new QSqlQueryModel();

        MainWindow db;
        db.connOpen();



        QSqlQuery qry;
        qry.prepare("SELECT Name, UserName, Cheq, Sav, SavAcct, CheqAcct FROM BANKING_CREDENTIALS");

        if(qry.exec()){
           qDebug()<<("In");


           model->setQuery(qry);
           ui->allCustomers->setModel(model);
           db.connClose();

        }else{
           qDebug()<<("out");
      }
}

AllCustomersView::~AllCustomersView()
{
    delete ui;
}

void AllCustomersView::on_backButton_clicked()
{
    this->hide();

    DeleteUser deleteUser;
    deleteUser.setModal(true);
    deleteUser.exec();
}
