#ifndef ALLCUSTOMERSVIEW_H
#define ALLCUSTOMERSVIEW_H

#include <QDialog>

namespace Ui {
class AllCustomersView;
}

class AllCustomersView : public QDialog
{
    Q_OBJECT

public:
    explicit AllCustomersView(QWidget *parent = 0);
    ~AllCustomersView();

private slots:
    void on_backButton_clicked();

private:
    Ui::AllCustomersView *ui;
};

#endif // ALLCUSTOMERSVIEW_H
