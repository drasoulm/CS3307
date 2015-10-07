#ifndef DELETEUSER_H
#define DELETEUSER_H

#include <QDialog>
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <managerlogin.h>
#include <customerlogin.h>
#include <QMessageBox>
#include <QDialog>
#include <mainwindow.h>
#include "QTableView"
#include "QTextEdit"
#include "QSqlQuery"

namespace Ui {
    class DeleteUser;


}

class DeleteUser : public QDialog
{
    Q_OBJECT

public:
      int cheq;
      int sav;
      int cheqBal;
      int savBal;

      QString cheqAcct;
      QString savAcct;
      QString name;

    explicit DeleteUser(QWidget *parent = 0);
    ~DeleteUser();

public slots:
     void updateCustomerInformation(double cheq, double sav, QTextEdit *hey, QSqlQuery qry2);

private slots:
    void on_searchButton_clicked();
    void on_closeChequing_clicked();
    void on_viewAll_clicked();
    void disableBtns(int cheq, int save, QPushButton *btn1, QPushButton *btn2, QPushButton *btn3);
    void on_backButton_clicked();

    void on_closeSav_clicked();

    void on_closeBoth_clicked();

private:
    Ui::DeleteUser *ui;

};

#endif // DELETEUSER_H
