#ifndef MAINTENANCEWINDOW_H
#define MAINTENANCEWINDOW_H

#include <QDialog>

namespace Ui {
class MaintenanceWindow ;
}

class MaintenanceWindow : public QDialog
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

    explicit MaintenanceWindow(QWidget *parent = 0);
    ~MaintenanceWindow();

private slots:
    void on_searchBtn_clicked();

private:
    Ui::MaintenanceWindow *ui;
};

#endif // MaintenanceWindow
