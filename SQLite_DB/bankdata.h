#ifndef BANKDATA_H
#define BANKDATA_H

#include <QDialog>

namespace Ui {
class BankData;
}

class BankData : public QDialog
{
    Q_OBJECT

public:
    explicit BankData(QWidget *parent = 0);
    ~BankData();

private:
    Ui::BankData *ui;
};

#endif // BANKDATA_H
