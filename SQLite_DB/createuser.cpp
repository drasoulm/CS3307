#include "createuser.h"
#include "ui_createuser.h"
#include "QInputDialog"
#include "QValidator"
#include "QLineEdit"

createuser::createuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createuser)
{
    ui->setupUi(this);
}

createuser::~createuser()
{
    delete ui;
}

void createuser::on_nextButton_clicked()
{
    QString password2, password, username, fullname;
    bool cheq, sav;
    double answerCheq, answerSav;
    int savAcct, cheqAcct;


    password = ui->password->text();
    password2 = ui->password2->text();
    username = ui->username->text();
    fullname = ui->fullname->text();
    cheq = ui->cheqBox->isChecked();
    sav = ui->savBox->isChecked();


    if (password != password2){

        QMessageBox::critical(this,tr("Error"),tr("Your Passwords Do Not Match! Try again...."));

    }else{

        MainWindow db;
        db.connOpen();

        if (cheq&&sav){
            answerCheq = QInputDialog::getDouble(this, "Creating Chequing Account..", "Deposit:");
            answerSav = QInputDialog::getDouble(this, "Creating Savings Account..", "Deposit:");
            cheqAcct = 1;
            savAcct = 1;
        }
        else if(cheq){

            answerCheq = QInputDialog::getDouble(this, "Creating Chequing Account..", "Deposit:");
            answerSav = 0.0;
            savAcct = 0;
            cheqAcct = 1;
        }
        else if(sav){

            answerSav = QInputDialog::getDouble(this, "Creating Savings Account..", "Deposit:",0,0,100000,2);
            answerCheq = 0.0;
            savAcct = 1;
            cheqAcct = 0;
        }


        QString str1= QString::number(answerCheq, 'f', 2);
        QString str2= QString::number(answerSav, 'f', 2);
        QString str3= QString::number(savAcct);
        QString str4= QString::number(cheqAcct);




        QSqlQuery qry;
        qry.prepare("INSERT INTO BANKING_CREDENTIALS (Name, Password, UserName, Manager, Cheq, Sav, CheqAcct, SavAcct) VALUES ('"+fullname+"','"+password+"','"+username+"',0,"+str2+","+str1+","+str4+","+str3+")");
        qDebug()<<(qry.lastQuery());
        if(qry.exec()){
           qDebug()<<("Inserted into DB");
           db.connClose();
           QMessageBox::information(this,tr("Account Created"),tr("Account has been created for user!"));

           this->hide();

           managerLogin managerLogin;
           managerLogin.setModal(true);
           managerLogin.exec();

        }
        else{
           QMessageBox::critical(this,tr("Woops..."),tr("ccc"));
           qDebug()<<("Not Inserted into DB");
           qDebug()<<(qry.lastError().text());
        }

    }




}
