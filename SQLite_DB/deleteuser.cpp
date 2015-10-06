#include "deleteuser.h"
#include "ui_deleteuser.h"
#include "allcustomersview.h"
#include "maintanenceview.h"
#include "helper.h"

/*Manager Actions*/
Helper helper;

extern struct Helper::currentClientInfo client;


DeleteUser::DeleteUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteUser)
{
    ui->setupUi(this);

    qDebug()<<(client.savBal);

}

DeleteUser::~DeleteUser()
{
    delete ui;
}

void DeleteUser::on_searchButton_clicked()
{
    //Search Name and maybe other things after
    name = ui->lineEdit->text();

    MainWindow db;
    db.connOpen();

    QSqlQuery qry2;
    qry2.prepare("SELECT * FROM BANKING_CREDENTIALS WHERE Name='"+name+"'");

    if(qry2.exec()){
       qry2.next();
       qDebug()<<(qry2.record());

       cheqBal = qry2.value(4).toInt();
       savBal = qry2.value(5).toInt();
       cheq = qry2.value(7).toInt();
       sav = qry2.value(6).toInt();
       name = qry2.value(0).toString();

       db.connClose();

       if(name.isEmpty()){
           QMessageBox::information(this,"Account","Couldn't find this person. Try again and remember - Firstname Lastname");
       }else {

           updateCustomerInformation(cheq, sav, ui->hey, qry2);
       }
          //Display user information in text area
    }
    else{
       qDebug()<<("Not Inserted into DB");
    }
    //Disable action buttons based on account... if cheq exists but sav doesnt, grey out 'CLOSE SAVINGS ACCOUNT' but 'CLOSE CHEQUING' enabled

     disableBtns(cheq, sav, ui->closeSav, ui->closeChequing, ui->closeBoth);

}

void DeleteUser::on_closeChequing_clicked()
{


    //Close chequing account
    if (cheqBal == 0){
          QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this,"Account","User only has a Chequing Account - close?",QMessageBox::Yes|QMessageBox::No);
          qDebug()<<(name);

      if(reply == QMessageBox::Yes){
          MainWindow db;
          db.connOpen();
          QSqlQuery qry;
          qry.prepare("UPDATE BANKING_CREDENTIALS SET CheqAcct=0 WHERE Name ='"+name+"'");
          qDebug()<<(qry.lastQuery());

          //have to check if they have a chequing account before you go with this function...

          if(qry.exec()){
             db.connClose();
             QMessageBox::information(this, name, "Chequing Account has been Deleted");


             MainWindow db;
             db.connOpen();

             QSqlQuery qry2;
             qry2.prepare("SELECT * FROM BANKING_CREDENTIALS WHERE Name='"+name+"'");

             if(qry2.exec()){
                Helper::currentClientInfo searchResult;
                searchResult = helper.createClient(qry2);

                db.connClose();
               //Update user information in text area
               updateCustomerInformation(searchResult.hasCheq, searchResult.hasSav, ui->hey, qry2);
               //Disable action buttons based on account... ex: if cheq exists but sav doesnt, grey out 'CLOSE SAVINGS ACCOUNT' but 'CLOSE CHEQUING ACCOUNT' enabled
               disableBtns(cheq, sav, ui->closeSav, ui->closeChequing, ui->closeBoth);
               this->show();

              }else{
                 QMessageBox::critical(this,tr("Woops..."),tr("Try Again. /n Error Code 22105"));
                 qDebug()<<("Not Inserted into DB");
                 qDebug()<<(qry.lastError().text());}
                }
        }else{

            QMessageBox::information(this,tr("Cancelled"),tr("Did not close chequing account"));
            }
    }else{
          QMessageBox::critical(this,tr("Can't..."),tr("Balance is not $0 - Ask Customer to empty funds"));
    }
}

void DeleteUser::on_viewAll_clicked()
{

    this->hide();
    AllCustomersView allcustomersview;
    allcustomersview.setModal(true);
    allcustomersview.exec();
}

void DeleteUser::disableBtns(int cheq, int sav, QPushButton *savBtn, QPushButton *cheqBtn, QPushButton *bothBtn){
//Disable buttons based on what accounts client currently holds
    if(cheq ==1 && sav ==1){
        cheqBtn->setEnabled(true);
        savBtn->setEnabled(true);
        bothBtn->setEnabled(true);
    } else if(cheq ==1 && sav ==0){
        cheqBtn->setEnabled(true);
        savBtn->setEnabled(false);
        bothBtn->setEnabled(false);
    } else if(cheq ==0 && sav ==1){
        cheqBtn->setEnabled(false);
        savBtn->setEnabled(true);
        bothBtn->setEnabled(false);
    }
}

void DeleteUser::updateCustomerInformation(int cheq, int sav, QTextEdit *hey, QSqlQuery qry2){
    if(sav==1 && cheq ==1){hey->setText("NAME: " + qry2.value(0).toString() + "\n" + "USERNAME:" + qry2.value(1).toString() + "\n" +"CHEQUING: $" + qry2.value(4).toString() + "\n" + "SAVINGS: $" + qry2.value(5).toString());
    }else if(sav==1&&cheq==0){hey->setText("NAME: " + qry2.value(0).toString() + "\n" + "USERNAME:" + qry2.value(1).toString() + "\n" + "SAVINGS: $" + qry2.value(5).toString() + "\n CHEQUING: NO CHEQUING ACCOUNT");
    }else if(sav==0&&cheq==1){hey->setText("NAME: " + qry2.value(0).toString() + "\n" + "USERNAME:" + qry2.value(1).toString() + "\n" +"CHEQUING: $" + qry2.value(4).toString() + "\n SAVINGS: NO SAVINGS ACCOUNT");
    }else if(sav==0&&cheq==0){hey->setText("NAME: " + qry2.value(0).toString() + "\n" + "USERNAME:" + qry2.value(1).toString() + "\n" +"CHEQUING: NO CHEQUING ACCOUNT" +"\n SAVINGS: NO SAVINGS ACCOUNT");}
}

