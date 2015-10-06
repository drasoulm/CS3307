#include "maintenancewindow.h"
#include "ui_MaintenanceWindow.h"
#include "deleteuser.h"

MaintenanceWindow::MaintenanceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaintenanceWindow)
{
    ui->setupUi(this);
}

MaintenanceWindow::~MaintenanceWindow()
{
    delete ui;
}

void MaintenanceWindow::on_searchBtn_clicked()
{
    //Search Name and maybe other things after
    name = ui->searchIn->text();

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
           QMessageBox::information(this,"Account","Couldn't this person. Try again and remember - Firstname Lastname");
       }else {
           DeleteUser updateTextArea;
           updateTextArea.updateCustomerInformation(cheq, sav, ui->customerInfo, qry2);
       }
          //Display user information in text area
    }
    else{
       qDebug()<<("Not Inserted into DB");
    }
    //Disable action buttons based on account... if cheq exists but sav doesnt, grey out 'CLOSE SAVINGS ACCOUNT' but 'CLOSE CHEQUING' enabled
}
