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

private slots:
    void on_depBtn_clicked();

    void on_widthBtn_clicked();

private:
    Ui::clientView *ui;
};

#endif // CLIENTVIEW_H
