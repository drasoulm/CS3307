#ifndef CUSTOMERLOGIN_H
#define CUSTOMERLOGIN_H
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <managerlogin.h>
#include <customerlogin.h>
#include <QMessageBox>
#include <QDialog>

namespace Ui {
class customerlogin;
}
class customerlogin : public QDialog
{
    Q_OBJECT

public:
    explicit customerlogin(QWidget *parent = 0);
    ~customerlogin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::customerlogin *ui;
};

#endif // CUSTOMERLOGIN_H
