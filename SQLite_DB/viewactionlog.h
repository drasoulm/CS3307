#ifndef VIEWACTIONLOG_H
#define VIEWACTIONLOG_H

#include <QDialog>

namespace Ui {
class ViewActionLog;
}

class ViewActionLog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewActionLog(QWidget *parent = 0);
    ~ViewActionLog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ViewActionLog *ui;
};

#endif // VIEWACTIONLOG_H
