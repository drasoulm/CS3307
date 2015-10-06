#ifndef ACCOUNTCREATE_H
#define ACCOUNTCREATE_H

#include <QDialog>

namespace Ui {
class accountCreate;
}

class accountCreate : public QDialog
{
    Q_OBJECT

public:
    explicit accountCreate(QWidget *parent = 0);
    ~accountCreate();

private:
    Ui::accountCreate *ui;
};

#endif // ACCOUNTCREATE_H
