#include "clientview.h"
#include "ui_clientview.h"
#include "helper.h"
#include "QInputDialog"

extern struct Helper::currentClientInfo client;

clientView::clientView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientView)
{

    ui->setupUi(this);

    QString saving = QString::number(client.savBal);
    QString chequing = QString::number(client.cheqBal);
    ui->sav->setText(saving);
    ui->cheq->setText(chequing);
}

clientView::~clientView()
{
    delete ui;
}

void clientView::on_depBtn_clicked()
{
    QMessageBox msgBox;

    msgBox.setText("Deposit");
    msgBox.setInformativeText("Where Would You Like to Deposit?");
    QPushButton *cheqButton = msgBox.addButton(tr("Chequing"), QMessageBox::ActionRole);
    QPushButton *savButton = msgBox.addButton(tr("Savings"),QMessageBox::ActionRole);
    QPushButton *cancel = msgBox.addButton(tr("Cancel"),QMessageBox::ActionRole);
    msgBox.exec();

    if(msgBox.clickedButton() == cheqButton){

        double answerCheq = QInputDialog::getDouble(this, "Deposting into Savings Account", "Deposit:",0,0,100000,2);

        client.cheqBal = client.cheqBal + answerCheq;
        QString cheq = QString::number(client.cheqBal);
        ui->cheq->setText(cheq);

        MainWindow db;
        db.connOpen();

        QSqlQuery qry2;
        qry2.prepare("UPDATE BANKING_CREDENTIALS SET Sav='"+cheq+"' WHERE name= '"+client.name+"'");

        if(qry2.exec()){
           QMessageBox::information(this,"Account","Done!");
           db.connClose();
           }
        else{
           qDebug()<<("Not Inserted into DB");
        }
    }else if(msgBox.clickedButton() == savButton){
        double answerSav = QInputDialog::getDouble(this, "Deposting into Savings Account", "Deposit:",0,0,100000,2);

        client.savBal = client.savBal + answerSav;
        QString sav = QString::number(client.savBal);
        ui->sav->setText(sav);

        MainWindow db;
        db.connOpen();

        QSqlQuery qry2;
        qry2.prepare("UPDATE BANKING_CREDENTIALS SET Cheq='"+sav+"' WHERE name= '"+client.name+"'");

        if(qry2.exec()){
           QMessageBox::information(this,"Account","Done!");
           db.connClose();
           }
        else{
           qDebug()<<("Not Inserted into DB");
        }
    }
}




void clientView::on_widthBtn_clicked()
{
    QMessageBox msgBox;

    msgBox.setText("Widthdrawl");
    msgBox.setInformativeText("Where Would You Like to Widthdrawl?");
    QPushButton *cheqButton = msgBox.addButton(tr("Chequing"), QMessageBox::ActionRole);
    QPushButton *savButton = msgBox.addButton(tr("Savings"),QMessageBox::ActionRole);
    QPushButton *cancel = msgBox.addButton(tr("Cancel"),QMessageBox::ActionRole);
    msgBox.exec();

    if(msgBox.clickedButton() == cheqButton){

        double answerCheq = QInputDialog::getDouble(this, "Widthdrawl from Chequing Account", "Widthdrawl:",0,0,100000,2);
        qDebug()<<(client.cheqBal);
        qDebug()<<(answerCheq);

        if(client.cheqBal - answerCheq < 0){
            QMessageBox::information(this,"Account","You don't have enough money! Find a better job - take out less..");

        }else{
                client.cheqBal = client.cheqBal - answerCheq;

                QString chequing = QString::number(client.cheqBal);
                qDebug()<<(chequing);
                ui->cheq->setText(chequing);

                MainWindow db;
                db.connOpen();

                QSqlQuery qry2;
                qry2.prepare("UPDATE BANKING_CREDENTIALS SET Cheq='"+chequing+"' WHERE name= '"+client.name+"'");

                if(qry2.exec()){
                  QMessageBox::information(this,"Account","Done!");
                   db.connClose();
                   }else{
                   qDebug()<<("Not Inserted into DB");
                }

            }

    }else if(msgBox.clickedButton() == savButton){

        double answerSav = QInputDialog::getDouble(this, "Widthdrawl from Savings Account", "Deposit:",0,0,100000,2);

        if(client.savBal - answerSav < 0){
            QMessageBox::information(this,"Account","You don't have enough money! Find a better job - take out less..");

        }else{
                client.savBal = client.savBal - answerSav;
                QString saving = QString::number(client.savBal);
                ui->sav->setText(saving);

                MainWindow db;
                db.connOpen();

                QSqlQuery qry2;
                qry2.prepare("UPDATE BANKING_CREDENTIALS SET Sav='"+saving+"' WHERE name= '"+client.name+"'");

                if(qry2.exec()){
                   QMessageBox::information(this,"Account","Done!");
                   db.connClose();
                   }
                else{
                   qDebug()<<("Not Inserted into DB");
                }

            }
    }
}
