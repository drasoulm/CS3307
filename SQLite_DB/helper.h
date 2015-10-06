#ifndef HELPER_H
#define HELPER_H

#include "QSqlQuery"
#include "mainwindow.h"

class Helper
{
public:
    Helper();
    struct currentClientInfo{
        QString name, ID, passWord;
        double cheqBal, savBal;
        int hasSav, hasCheq,manager,maintPers, isTrail;
     };

signals:

public slots:
    struct Helper::currentClientInfo createClient(QSqlQuery qry);
};

#endif // HELPER_H
