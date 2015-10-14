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
    qDebug()<<(client.hasCheq);
    qDebug()<<(client.hasSav);
    if(client.hasCheq == 1 && client.hasSav == 1){
        ui->sav->setText(saving);
        ui->cheq->setText(chequing);
    }else if(client.hasCheq == 0 && client.hasSav == 1){
        ui->sav->setText(saving);
        ui->cheq->setText("NO ACCOUNT");
    }else if(client.hasCheq == 1 && client.hasSav == 0){
        ui->sav->setText("NO ACCOUNT");
        ui->cheq->setText(chequing);
    }else{
        ui->sav->setText("NO ACCOUNT");
        ui->cheq->setText("NO ACCOUNT");
    }
}

clientView::~clientView()
{
    delete ui;
}

void clientView::on_depBtn_clicked()
{
    QMessageBox msgBox;
    MaintanenceView mainview;

    msgBox.setText("Deposit");
    msgBox.setInformativeText("Where Would You Like to Deposit?");
    QPushButton *cheqButton = msgBox.addButton(tr("Chequing"), QMessageBox::ActionRole);
    QPushButton *savButton = msgBox.addButton(tr("Savings"),QMessageBox::ActionRole);
    msgBox.exec();

    if(msgBox.clickedButton() == cheqButton && client.hasCheq == 1){
        bool ok;
        double answerCheq = QInputDialog::getDouble(this, "Deposting into Savings Account", "Deposit:",0,0,100000,2, &ok);
        QString amount = QString::number(answerCheq);
        if(ok){
            client.cheqBal = client.cheqBal + answerCheq;
            QString cheq = QString::number(client.cheqBal);
            ui->cheq->setText(cheq);

            MainWindow db;
            db.connOpen();

            QSqlQuery qry2;
            qry2.prepare("UPDATE BANKING_CREDENTIALS SET Sav='"+cheq+"' WHERE name= '"+client.name+"'");

            if(qry2.exec()){
                QString action = "DEPOSITED TO SAV: $"+amount+"";
                //Log
                mainview.isTrail(client.isTrail, action);
               QMessageBox::information(this,"Account","Done!");
               db.connClose();
               }
            else{
               qDebug()<<("Not Inserted into DB");
            }

        }else{
            QMessageBox::information(this,"Cancelled","Cancelled");
        }
    }else if(msgBox.clickedButton() == savButton && client.hasSav==1){
        bool ok;
        double answerSav = QInputDialog::getDouble(this, "Deposting into Savings Account", "Deposit:",0,0,100000,2,&ok);
        QString amount = QString::number(answerSav);

        if(ok){
                client.savBal = client.savBal + answerSav;
                QString sav = QString::number(client.savBal);
                ui->sav->setText(sav);

                MainWindow db;
                db.connOpen();

                QSqlQuery qry2;
                qry2.prepare("UPDATE BANKING_CREDENTIALS SET Cheq='"+sav+"' WHERE name= '"+client.name+"'");

                    if(qry2.exec()){
                       QMessageBox::information(this,"Account","Done!");
                       //Log
                       QString action = "DEPOSITED TO CHEQ: $"+amount+"";
                       mainview.isTrail(client.isTrail, action);
                       db.connClose();
                       }
                    else{
                       qDebug()<<("Not Inserted into DB");
                    }

               }else{
                    QMessageBox::information(this,"Cancelled","Cancelled");
                }
    }else if(client.hasCheq == 0 || client.hasSav ==0){
        QMessageBox::information(this,"Cancelled Transfer","You don't have an account, request one!");

    }else{
        QMessageBox::information(this,"Cancelled Transfer","Cancelled Transfer");

    }
}




void clientView::on_widthBtn_clicked()
{
    QMessageBox msgBox;
    MaintanenceView mainview;

    msgBox.setText("Widthdrawl");
    msgBox.setInformativeText("Where Would You Like to Widthdrawl?");
    QPushButton *cheqButton = msgBox.addButton(tr("Chequing"), QMessageBox::ActionRole);
    QPushButton *savButton = msgBox.addButton(tr("Savings"),QMessageBox::ActionRole);
    QPushButton *cancel = msgBox.addButton(tr("Cancel"),QMessageBox::ActionRole);
    msgBox.exec();

    if(msgBox.clickedButton() == cheqButton && client.hasCheq == 1){

        bool ok;
        double answerCheq = QInputDialog::getDouble(this, "Widthdrawl from Chequing Account", "Widthdrawl:",0,0,100000,2, &ok);
        QString amount = QString::number(answerCheq);
        if(ok){
                double sum = client.cheqBal - answerCheq;
                if(sum <= 0){
                    QMessageBox::information(this,"Account","You don't have enough money!");

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
                            QString action = "WIDTHDREW FROM CHEQ: $"+amount+"";
                            mainview.isTrail(client.isTrail, action);
                          QMessageBox::information(this,"Account","Done!");
                           db.connClose();
                           }else{
                           qDebug()<<("Not Inserted into DB");
                        }

                    }
        }else{
            QMessageBox::information(this,"Cancelled","Cancelled");
        }

    }else if(msgBox.clickedButton() == savButton && client.hasSav == 1){

        bool ok;
        double answerSav = QInputDialog::getDouble(this, "Widthdrawl from Savings Account", "Widthdrawl:",0,0,100000,2, &ok);
        QString amount = QString::number(answerSav);
        if(ok){
                if(client.savBal - answerSav < 0){
                    QMessageBox::information(this,"Account","You don't have enough money! Find a better job - take out less..");

                }else{
                        client.savBal = client.savBal - answerSav;
                        qDebug()<<(client.savBal);
                        QString saving = QString::number(client.savBal);
                        ui->sav->setText(saving);

                        MainWindow db;
                        db.connOpen();

                        QSqlQuery qry2;
                        qry2.prepare("UPDATE BANKING_CREDENTIALS SET Sav='"+saving+"' WHERE name= '"+client.name+"'");
                        QString action = "WIDTHDREW FROM SAV: $"+amount+"";
                        mainview.isTrail(client.isTrail, action);

                        if(qry2.exec()){
                           QMessageBox::information(this,"Account","Done!");
                           db.connClose();
                           }
                        else{
                           qDebug()<<("Not Inserted into DB");
                        }

                    }
        }else if(client.hasCheq ==0 || client.hasSav ==0){
            QMessageBox::information(this,"Cancelled Transfer","You don't have an account, request one!"); //Client doesn't have account yet and must request one.
        }else{
            QMessageBox::information(this,"Cancelled","Cancelled");

        }
    }
}

void clientView::on_transBtn_clicked()
{
    QMessageBox msgBox;
    MaintanenceView mainview;

    msgBox.setText("Transfer");
    msgBox.setInformativeText("Transfer from which account?");
    QPushButton *cheqButton = msgBox.addButton(tr("Chequing"), QMessageBox::ActionRole);
    QPushButton *savButton = msgBox.addButton(tr("Savings"),QMessageBox::ActionRole);
    QPushButton *cancel = msgBox.addButton(tr("Cancel"),QMessageBox::ActionRole);
    msgBox.exec();

    if(msgBox.clickedButton() == cheqButton && client.hasCheq == 1 && client.hasSav == 1){
        bool ok;
        double answerCheq = QInputDialog::getDouble(this, "How much would you like to transfer to your savings account?", "Transfer:",0,0,100000,2, &ok);
        QString amount = QString::number(answerCheq);

        if(ok){

            double enough = client.cheqBal - answerCheq; //Check to see if client is trying to transfer more than what he/she has
            if(enough > 0){  //Client has enough money

                if(enough < 1000){ //If client's balance goes under $1000 then warn them..

                    QMessageBox thresholdWarning;

                    thresholdWarning.setText("Warning");
                    thresholdWarning.setInformativeText("$2.00 Charge for transfering any money with a balance below $1000");
                    QPushButton *Transfer = thresholdWarning.addButton(tr("Transfer Anyways"), QMessageBox::ActionRole);
                    QPushButton *cancel = thresholdWarning.addButton(tr("Don't Transfer"),QMessageBox::ActionRole);
                    thresholdWarning.exec();
                    if(thresholdWarning.clickedButton() == Transfer){ //If client clicks ok after warning msg go ahead..
                            enough = client.cheqBal - answerCheq - 2; //Charge client $2.00
                            if(enough >= 0){ //Check to see if balance is still above 0 after charge..
                                client.cheqBal = client.cheqBal - answerCheq - 2; //Calculate current balance after transfer and charge
                                client.savBal = client.savBal + answerCheq - 2; //Calculate new saving balance after transfer
                                QString cheq = QString::number(client.cheqBal, 'f', 2);
                                QString sav = QString::number(client.savBal, 'f', 2);
                                ui->cheq->setText(cheq);//Update labels on UI
                                ui->sav->setText(sav); //Update labels on UI
                                /*UPDATE DB*/
                                MainWindow db;
                                db.connOpen();

                                QSqlQuery qry2;
                                qry2.prepare("UPDATE BANKING_CREDENTIALS SET Cheq='"+cheq+"', Sav='"+sav+"' WHERE name= '"+client.name+"'");
                                QString action = "TRANSFERED TO CHEQ FROM SAV AND CHARGED $2: $"+amount+"";
                                mainview.isTrail(client.isTrail, action);

                                if(qry2.exec()){
                                   QMessageBox::information(this,"Account","Done!");
                                   db.connClose();
                                   }
                                else{
                                   qDebug()<<("Not Inserted into DB");
                                }
                            }else{
                                QMessageBox::information(this,"Cancelled","You don't have enough money."); //If they have less than $0 after $2 charge then cancel out and let them know that the transfer didn't go thru
                            }
                    }
                }else{ //Clients balance will not go under $1000...
                    client.cheqBal = client.cheqBal - answerCheq; //Calculate new chequing balance
                    client.savBal = client.savBal + answerCheq; //Calculate new savings balance
                    QString cheq = QString::number(client.cheqBal, 'f', 2);
                    QString sav = QString::number(client.savBal, 'f', 2);

                    ui->cheq->setText(cheq);
                    ui->sav->setText(sav);

                    MainWindow db;
                    db.connOpen();

                    QSqlQuery qry2;
                    qry2.prepare("UPDATE BANKING_CREDENTIALS SET Sav='"+sav+"',Cheq='"+cheq+"' WHERE name= '"+client.name+"'");

                    if(qry2.exec()){
                        //Log
                        QString action = "TRANSFERED TO CHEQ FROM SAV: "+amount+"";
                        mainview.isTrail(client.isTrail, action);
                       QMessageBox::information(this,"Account","Done!");
                       db.connClose();
                       }
                    else{
                       qDebug()<<("Not Inserted into DB");
                    }
                }
            }else{
                QMessageBox::information(this,"Cancelled","You don't have enough money.");
            }

        }else{
            QMessageBox::information(this,"Cancelled","Cancelled");
        }
    }else if(msgBox.clickedButton() == savButton && client.hasCheq == 1 && client.hasSav == 1){
        bool ok;
        double answerSav = QInputDialog::getDouble(this, "How much would you like to transfer to your chequing account?", "Transfer:",0,0,100000,2, &ok);
        QString amount = QString::number(answerSav);

        if(ok){

            double enough = client.savBal - answerSav; //Check to see if client is trying to transfer more than what he/she has
            if(enough > 0){  //Client has enough money

                if(enough < 1000){ //If client's balance goes under $1000 then warn them..

                    QMessageBox thresholdWarning;

                    thresholdWarning.setText("Warning");
                    thresholdWarning.setInformativeText("$2.00 Charge for transfering any money with a balance below $1000");
                    QPushButton *Transfer = thresholdWarning.addButton(tr("Transfer Anyways"), QMessageBox::ActionRole);
                    QPushButton *cancel = thresholdWarning.addButton(tr("Don't Transfer"),QMessageBox::ActionRole);
                    thresholdWarning.exec();
                    if(thresholdWarning.clickedButton() == Transfer){ //If client clicks ok after warning msg go ahead..
                        qDebug()<<("got here");
                            enough = client.savBal - answerSav - 2; //Charge client $2.00
                            if(enough >= 0){ //Check to see if balance is still above 0 after charge..
                                client.cheqBal = client.cheqBal + answerSav - 2; //Calculate current balance after transfer and charge
                                client.savBal = client.savBal - answerSav - 2; //Calculate new saving balance after transfer
                                QString cheq = QString::number(client.cheqBal, 'f', 2);
                                QString sav = QString::number(client.savBal, 'f', 2);
                                ui->cheq->setText(cheq);//Update labels on UI
                                ui->sav->setText(sav); //Update labels on UI
                                /*UPDATE DB*/
                                MainWindow db;
                                db.connOpen();

                                QSqlQuery qry2;
                                qry2.prepare("UPDATE BANKING_CREDENTIALS SET Cheq='"+cheq+"', Sav='"+sav+"' WHERE name= '"+client.name+"'");

                                if(qry2.exec()){
                                    //Log
                                    QString action = "TRANSFERED TO CHEQ FROM SAV AND CHARGED $2:$ "+amount+"";
                                    mainview.isTrail(client.isTrail, action);
                                   QMessageBox::information(this,"Account","Done!");
                                   db.connClose();
                                   }
                                else{
                                   qDebug()<<("Not Inserted into DB");
                                }
                            }else{
                                QMessageBox::information(this,"Cancelled","You don't have enough money."); //If they have less than $0 after $2 charge then cancel out and let them know that the transfer didn't go thru
                            }
                    }
                }else{ //Clients balance will not go under $1000...
                    client.cheqBal = client.cheqBal + answerSav; //Calculate new chequing balance
                    client.savBal = client.savBal - answerSav; //Calculate new savings balance
                    QString cheq = QString::number(client.cheqBal, 'f', 2);
                    QString sav = QString::number(client.savBal, 'f', 2);

                    ui->cheq->setText(cheq);
                    ui->sav->setText(sav);

                    MainWindow db;
                    db.connOpen();

                    QSqlQuery qry2;
                    qry2.prepare("UPDATE BANKING_CREDENTIALS SET Sav='"+sav+"',Cheq='"+cheq+"' WHERE name= '"+client.name+"'");
                    //Log
                    QString action = "TRANSFERED TO CHEQ FROM SAV: $"+amount+"";
                    mainview.isTrail(client.isTrail, action);

                    if(qry2.exec()){
                       QMessageBox::information(this,"Account","Done!");
                       db.connClose();
                       }
                    else{
                       qDebug()<<("Not Inserted into DB");
                    }
                }
            }else{
                QMessageBox::information(this,"Cancelled","You don't have enough money.");
            }

        }else{
            QMessageBox::information(this,"Cancelled","Cancelled");
        }
    }
}

void clientView::on_reqBtn_clicked() /*Request to open or close an account*/
{
    MaintanenceView mainview;
    qDebug()<<(client.cheqBal);
    QMessageBox accountClose; //Ask client what they would like to close
    accountClose.setText("What would you like to close?");
    accountClose.setInformativeText("Which account would you like to close?");
    QPushButton *Chequing = accountClose.addButton(tr("Request Chequing"), QMessageBox::ActionRole);
    QPushButton *Savings = accountClose.addButton(tr("Request Savings"),QMessageBox::ActionRole);
    QPushButton *Both = accountClose.addButton(tr("Both"),QMessageBox::ActionRole);
    accountClose.exec();

    if(accountClose.clickedButton() == Chequing && client.cheqBal == 0){ //If they want to close chequing
        //Log action to file
        QString action = "REQUESTING CLOSURE OF ACCOUNT: CHEQ";
        mainview.isTrail(client.isTrail, action);

        QSqlQuery insert;
        insert.prepare("INSERT INTO CLIENT_REQUEST (name, openSav, openCheq, done) VALUES('"+client.name+"', 0,1,0)");
        insert.exec();
        QMessageBox::information(this,"Done","Your request will be completed in the next 24 hours");

    }else if(accountClose.clickedButton() == Savings && client.savBal == 0){ //If they want to close savings
        QString action = "REQUESTING CLOSURE OF ACCOUNT: SAV";
        mainview.isTrail(client.isTrail, action);

        QSqlQuery insert;
        insert.prepare("INSERT INTO CLIENT_REQUEST (name, openSav, openCheq, done) VALUES('"+client.name+"', 1,0,0)");
        insert.exec();
        QMessageBox::information(this,"Done","Your request will be completed in the next 24 hours");

    }else if(accountClose.clickedButton() == Both && client.cheqBal == 0 && client.savBal == 0){ //If they want to close both (create two tickets)
        QString action = "REQUESTING CLOSURE OF ACCOUNT: CHEQ & SAV";
        mainview.isTrail(client.isTrail, action);
        QSqlQuery insert;
        insert.prepare("INSERT INTO CLIENT_REQUEST (name, openSav, openCheq, done) VALUES('"+client.name+"', 1,0,0)");
        insert.prepare("INSERT INTO CLIENT_REQUEST (name, openSav, openCheq, done) VALUES('"+client.name+"', 0,1,0)");
        insert.exec();

        QMessageBox::information(this,"Done","Your request will be completed in the next 24 hours");

    }else{
        QMessageBox::information(this,"Cancelled","Please empty your funds before submitting a request");
    }



}
