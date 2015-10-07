#include "deleteuser.h"
#include "ui_deleteuser.h"
#include "allcustomersview.h"
#include "maintanenceview.h"
#include "helper.h"

/*Manager Actions*/
Helper helper;

extern struct Helper::currentClientInfo client;
Helper::currentClientInfo searchResult;


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

       searchResult.cheqBal = qry2.value(4).toDouble();
       searchResult.savBal = qry2.value(5).toDouble();
       searchResult.hasCheq = qry2.value(7).toInt();
       searchResult.hasSav = qry2.value(6).toInt();
       searchResult.name = qry2.value(0).toString();

       qDebug()<<(searchResult.hasCheq);

       db.connClose();

       if(name.isEmpty()){
           QMessageBox::information(this,"Account","Couldn't find this person. Try again and remember - Firstname Lastname");
       }else {
           updateCustomerInformation(searchResult.cheqBal, searchResult.savBal, ui->hey, qry2);
           //Disable action buttons based on account... if cheq exists but sav doesnt, grey out 'CLOSE SAVINGS ACCOUNT' but 'CLOSE CHEQUING' enabled
           disableBtns(searchResult.hasCheq, searchResult.hasSav, ui->closeSav, ui->closeChequing, ui->closeBoth);
       }
    }
    else{
       qDebug()<<("Not Inserted into DB");
    }
}

void DeleteUser::on_closeChequing_clicked()
{


    //Close chequing account
    if (searchResult.cheqBal == 0){
          QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this,"Account","User only has a Chequing Account - close?",QMessageBox::Yes|QMessageBox::No);
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
                qry.next();
                Helper::currentClientInfo searchResult;
                searchResult = helper.createClient(qry2);

                db.connClose();
               //Update user information in text area
               updateCustomerInformation(searchResult.hasCheq, searchResult.hasSav, ui->hey, qry2);
               //Disable action buttons based on account... ex: if cheq exists but sav doesnt, grey out 'CLOSE SAVINGS ACCOUNT' but 'CLOSE CHEQUING ACCOUNT' enabled
               disableBtns(searchResult.hasCheq, searchResult.hasSav, ui->closeSav, ui->closeChequing, ui->closeBoth);
               this->show();

              }else{
                 QMessageBox::critical(this,tr("Woops..."),tr("Query did not run!"));
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
    }else{
        cheqBtn->setEnabled(false);
        savBtn->setEnabled(false);
        bothBtn->setEnabled(false);
    }
}

void DeleteUser::updateCustomerInformation(double cheq, double sav, QTextEdit *hey, QSqlQuery qry2){
    if(sav==1 && cheq ==1){hey->setText("NAME: " + qry2.value(0).toString() + "\n" + "USERNAME:" + qry2.value(1).toString() + "\n" +"CHEQUING: $" + qry2.value(4).toString() + "\n" + "SAVINGS: $" + qry2.value(5).toString());
    }else if(sav==1&&cheq==0){hey->setText("NAME: " + qry2.value(0).toString() + "\n" + "USERNAME:" + qry2.value(1).toString() + "\n" + "SAVINGS: $" + qry2.value(5).toString() + "\n CHEQUING: NO CHEQUING ACCOUNT");
    }else if(sav==0&&cheq==1){hey->setText("NAME: " + qry2.value(0).toString() + "\n" + "USERNAME:" + qry2.value(1).toString() + "\n" +"CHEQUING: $" + qry2.value(4).toString() + "\n SAVINGS: NO SAVINGS ACCOUNT");
    }else if(sav==0&&cheq==0){hey->setText("NAME: " + qry2.value(0).toString() + "\n" + "USERNAME:" + qry2.value(1).toString() + "\n" +"CHEQUING: NO CHEQUING ACCOUNT" +"\n SAVINGS: NO SAVINGS ACCOUNT");}
}


void DeleteUser::on_backButton_clicked()
{
    this->hide();

    managerLogin managerView;
    managerView.setModal(true);
    managerView.exec();
}

void DeleteUser::on_closeSav_clicked()
{
    //Close chequing account
    if (searchResult.savBal == 0){
          QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this,"Account","Close Savings Account?",QMessageBox::Yes|QMessageBox::No);
          qDebug()<<(name);

      if(reply == QMessageBox::Yes){
          MainWindow db;
          db.connOpen();
          QSqlQuery qry;
          qry.prepare("UPDATE BANKING_CREDENTIALS SET SavAcct=0 WHERE Name ='"+name+"'");
          qDebug()<<(qry.lastQuery());

          if(qry.exec()){
             db.connClose();
             QMessageBox::information(this, name, "Saving's Account has been Deleted");

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
               disableBtns(searchResult.hasCheq, searchResult.hasSav, ui->closeSav, ui->closeChequing, ui->closeBoth);
               this->show();

              }else{
                 QMessageBox::critical(this,tr("Woops..."),tr("Query did not run!"));
                 qDebug()<<("Not Inserted into DB");
                 qDebug()<<(qry.lastError().text());}
                }
        }else{

            QMessageBox::information(this,tr("Cancelled"),tr("Did not close Savings account"));
            }
    }else{
          QMessageBox::critical(this,tr("Can't..."),tr("Balance is not $0 - Ask Customer to empty funds out of Savings before you cancel"));
    }
}

void DeleteUser::on_closeBoth_clicked()
{
    //Close chequing account
    if (searchResult.savBal == 0 && searchResult.cheqBal ==0){
          QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this,"Account","Close Saving's AND Chequing Accounts?",QMessageBox::Yes|QMessageBox::No);

      if(reply == QMessageBox::Yes){
          MainWindow db;
          db.connOpen();
          QSqlQuery qry;
          qry.prepare("UPDATE BANKING_CREDENTIALS SET SavAcct=0, CheqAcct=0 WHERE Name ='"+name+"'");
          qDebug()<<(qry.lastQuery());

          if(qry.exec()){
             db.connClose();
             QMessageBox::information(this, name, "Saving's and Chequing Account have been closed");

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
               disableBtns(searchResult.hasCheq, searchResult.hasSav, ui->closeSav, ui->closeChequing, ui->closeBoth);
               this->show();

              }else{
                 QMessageBox::critical(this,tr("Woops..."),tr("Query did not run!"));
                 qDebug()<<("Not Inserted into DB");
                 qDebug()<<(qry.lastError().text());}
                }
        }else{

            QMessageBox::information(this,tr("Cancelled"),tr("Did not close any accounts"));
            }
    }else{
          QMessageBox::critical(this,tr("Can't..."),tr("Balance is not $0 - Ask Customer to empty funds out of Savings and Chequing before you cancel both"));
    }
}
