#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <managerlogin.h>
#include <customerlogin.h>
#include <QMessageBox>
#include "QFileInfo"
#include "clientview.h"
#include "maintanenceview.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

       void connClose();

       bool connOpen();
       bool fileExists(QString path);

       void createDBFileThenTable();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
