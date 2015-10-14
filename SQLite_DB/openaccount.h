#ifndef OPENACCOUNT_H
#define OPENACCOUNT_H

#include <QDialog>
#include "helper.h"

namespace Ui {
class OpenAccount;
}

class OpenAccount : public QDialog
{
    Q_OBJECT

public:
    QString name;
    Helper::currentClientInfo searchRes;
    explicit OpenAccount(QWidget *parent = 0);
    ~OpenAccount();

private slots:
    void on_searchBtn_clicked();

    void on_openCheq_clicked();

    void on_openSav_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::OpenAccount *ui;
};

#endif // OPENACCOUNT_H
