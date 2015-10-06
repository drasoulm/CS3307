#include "maintanenceview.h"
#include "ui_maintanenceview.h"
#include "customerlog.h"

MaintanenceView::MaintanenceView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaintanenceView)
{
    ui->setupUi(this);
}

MaintanenceView::~MaintanenceView()
{
    delete ui;
}

bool MaintanenceView::isTrail(int trace, QString action){
    customerLog logAction;
    if(trace == 1){
        logAction.customerActionToLog(action);
        return true;
    }else{
        return false;
    }
}
