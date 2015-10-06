#include "clientview.h"
#include "ui_clientview.h"
#include "helper.h"

extern struct Helper::currentClientInfo client;

clientView::clientView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientView)
{
    ui->setupUi(this);
}

clientView::~clientView()
{
    delete ui;
}
