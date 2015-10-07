#include "maintanenceview.h"
#include "ui_maintanenceview.h"
#include "customerlog.h"
#include "helper.h"

Helper::currentClientInfo res;
extern struct Helper::currentClientInfo client;
MaintanenceView::MaintanenceView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaintanenceView)
{
    ui->setupUi(this);

    if(client.isTrail == 1){
        ui->traceBtn->setText("Turn OFF Execution Tracing");
    }else{
        ui->traceBtn->setText("Turn ON Execution Tracing");
    }
}

MaintanenceView::~MaintanenceView()
{
    delete ui;
}


bool MaintanenceView::isTrail(int trace, QString action){
    customerLog logAction;
    if(trace == 1){
        logAction.customerActionToLog(action);
        return true;
    }else{
        return false;
    }
}



void MaintanenceView::on_traceBtn_clicked()
{
    if(client.isTrail == 0){
        MainWindow db;
        db.connOpen();

        QSqlQuery qry2;
        qry2.prepare("UPDATE BANKING_CREDENTIALS SET execTrace = 1");

        if(qry2.exec()){
            client.isTrail = 1;
            QMessageBox::information(this,"Tracing..","Execution Tracing is now ON and will be outputed to a log file");
            ui->traceBtn->setText("Turn OFF Execution Tracing");

           db.connClose();
        }
        else{
           qDebug()<<("Could not turn on exection trace please try again..");
        }
    }else if(client.isTrail == 1){
        MainWindow db;
        db.connOpen();

        QSqlQuery qry2;
        qry2.prepare("UPDATE BANKING_CREDENTIALS SET execTrace = 0");

        if(qry2.exec()){
            client.isTrail = 0;
            QMessageBox::information(this,"Tracing..","Execution Tracing is now OFF and will NOT be outputed to log file");
            ui->traceBtn->setText("Turn ON Execution Tracing");

           db.connClose();
        }
        else{
           qDebug()<<("Could not turn off exection trace please try again..");
        }
    }
}
