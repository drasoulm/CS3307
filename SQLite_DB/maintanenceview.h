#ifndef MAINTANENCEVIEW_H
#define MAINTANENCEVIEW_H

#include <QDialog>

namespace Ui {
class MaintanenceView;
}

class MaintanenceView : public QDialog
{
    Q_OBJECT

public:
    explicit MaintanenceView(QWidget *parent = 0);
    ~MaintanenceView();

public slots:
     bool isTrail(int trace, QString action);

private slots:

     void on_traceBtn_clicked();

private:
    Ui::MaintanenceView *ui;
};

#endif // MAINTANENCEVIEW_H
