#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H

#include <QDialog>
#include "mainwindow.h"
#include "customerlog.h"

namespace Ui {
class clientView;
}

class clientView : public QDialog
{
    Q_OBJECT

public:
    explicit clientView(QWidget *parent = 0);
    ~clientView();

private:
    Ui::clientView *ui;
};

#endif // CLIENTVIEW_H
