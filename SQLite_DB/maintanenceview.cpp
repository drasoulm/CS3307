#include "maintanenceview.h"
#include "ui_maintanenceview.h"
#include "customerlog.h"
#include "helper.h"
#include <QApplication>
#include "viewactionlog.h"

Helper::currentClientInfo res; //resulting client used for searches
extern struct Helper::currentClientInfo client; //Currently logged on client
MaintanenceView::MaintanenceView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaintanenceView)
{
    ui->setupUi(this);
    /*Check to see if client has execution tracing on*/
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


bool MaintanenceView::isTrail(int trace, QString action){ //Function return true if the client has tracing turned on
    customerLog logAction;
    if(trace == 1){
        logAction.customerActionToLog(action);
        return true;
    }else{
        return false;
    }
}



void MaintanenceView::on_traceBtn_clicked() //Trace Button to turn tracing on or off by Maintanence person
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

void MaintanenceView::on_pushButton_clicked()
{
    this->hide();
    ViewActionLog val;
    val.setModal(true);
    val.exec();
}
