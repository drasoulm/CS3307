#ifndef CREATEUSER_H
#define CREATEUSER_H
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <managerlogin.h>
#include <customerlogin.h>
#include <deleteuser.h>
#include <QMessageBox>
#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class createuser;
}

class createuser : public QDialog
{
    Q_OBJECT

public:
    explicit createuser(QWidget *parent = 0);
    ~createuser();

private slots:
    void on_nextButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::createuser *ui;
};

#endif // CREATEUSER_H
