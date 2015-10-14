#ifndef MANAGERLOGIN_H
#define MANAGERLOGIN_H
#include <createuser.h>
#include<deleteuser.h>
#include <QDialog>

namespace Ui {
class managerLogin;
}

class managerLogin : public QDialog
{
    Q_OBJECT

public:
    explicit managerLogin(QWidget *parent = 0);
    ~managerLogin();

private slots:
    void on_createAcc_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::managerLogin *ui;
};

#endif // MANAGERLOGIN_H
