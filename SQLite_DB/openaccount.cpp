#include "openaccount.h"
#include "ui_openaccount.h"
#include "helper.h"
#include "QInputDialog"

 //Search Result for client
OpenAccount::OpenAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenAccount)
{
    ui->setupUi(this);
}

OpenAccount::~OpenAccount()
{
    delete ui;
}

void OpenAccount::on_searchBtn_clicked()
{
    //Search Name and maybe other things after
    name = ui->nameIn->text();

    MainWindow db;
    db.connOpen();

    QSqlQuery qry2;
    qry2.prepare("SELECT * FROM BANKING_CREDENTIALS WHERE Name='"+name+"'");

    if(qry2.exec()){
       qry2.next();
       qDebug()<<(qry2.record());

       searchRes.cheqBal = qry2.value(4).toDouble();
       searchRes.savBal = qry2.value(5).toDouble();
       searchRes.hasCheq = qry2.value(7).toInt();
       searchRes.hasSav = qry2.value(6).toInt();
       searchRes.name = qry2.value(0).toString();
       searchRes.ID = qry2.value(1).toString();

       db.connClose();

       if(name.isEmpty()){
           QMessageBox::information(this,"Account","Couldn't find this person. Try again and remember - Firstname Lastname");
       }else {
           DeleteUser du;

           du.updateCustomerInformation(searchRes.hasCheq, searchRes.hasSav, ui->userInfo, qry2);
           if(searchRes.hasCheq == 1){
               ui->openCheq->setEnabled(false);
           }
           if(searchRes.hasSav==1){
               ui->openSav->setEnabled(false);
           }
       }
    }
    else{
       qDebug()<<("Not Inserted into DB");
    }
}

void OpenAccount::on_openCheq_clicked() //Open Chequing account for user
{
       double answerCheq;
       int cheqAcct;

        MainWindow db;
        db.connOpen();

        answerCheq = QInputDialog::getDouble(this, "Creating Chequing Account..", "Deposit:",0,0,100000,2);
        cheqAcct = 1;

        QString str1= QString::number(answerCheq, 'f', 2);
        QString str4= QString::number(cheqAcct);

        QSqlQuery qry, qry2;
        qry.prepare("UPDATE BANKING_CREDENTIALS SET Cheq="+str1+", CheqAcct="+str4+" WHERE UserName='"+searchRes.ID+"'");
        qDebug()<<(qry.lastQuery());
        qry2.prepare("SELECT * FROM BANKING_CREDENTIALS WHERE UserName='"+searchRes.ID+"'");
        if(qry.exec()){

            qry2.exec(); //Update customer information in text area
            DeleteUser du;
            du.updateCustomerInformation(searchRes.hasCheq, searchRes.hasSav, ui->userInfo, qry2);

            qDebug()<<(qry.lastQuery());
            ui->openCheq->setEnabled(false);
           qDebug()<<("Inserted into DB");
           db.connClose();
           QMessageBox::information(this,tr("Account Created"),tr("Account has been created for user!"));

        }
        else{
           QMessageBox::critical(this,tr("Woops..."),tr("Try Again"));
           qDebug()<<("Not Inserted into DB");
           qDebug()<<(qry.lastError().text());
        }
}

void OpenAccount::on_openSav_clicked() //Open Savings account for user
{

        bool sav;
        double answerSav;
        int savAcct;

        MainWindow db;
        db.connOpen();

        answerSav = QInputDialog::getDouble(this, "Creating Chequing Account..", "Deposit:",0,0,100000,2);
        savAcct = 1;

        QString str1= QString::number(answerSav, 'f', 2);
        QString str4= QString::number(savAcct);

        QSqlQuery qry;
        qry.prepare("UPDATE BANKING_CREDENTIALS SET Sav="+str1+", SavAcct="+str4+" WHERE UserName='"+searchRes.ID+"'");
        qDebug()<<(qry.lastQuery());
        if(qry.exec()){
            ui->openSav->setEnabled(false);
           qDebug()<<("Inserted into DB");
           db.connClose();
           QMessageBox::information(this,tr("Account Created"),tr("Account has been created for user!"));

        }
        else{
           QMessageBox::critical(this,tr("Woops..."),tr("Try Again"));
           qDebug()<<("Not Inserted into DB");
           qDebug()<<(qry.lastError().text());
        }
}

void OpenAccount::on_pushButton_2_clicked() //go back to manager dash
{
    this->hide();
    managerLogin ML;
    ML.setModal(true);
    ML.exec();
}
