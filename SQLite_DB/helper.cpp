#include "helper.h"

Helper::Helper()
{

}

struct Helper::currentClientInfo Helper::createClient(QSqlQuery qry){

    struct Helper::currentClientInfo searchResult;
    searchResult.name = qry.value(0).toString();
    searchResult.cheqBal = qry.value(4).toInt();
    searchResult.savBal = qry.value(5).toInt();
    searchResult.hasCheq = qry.value(7).toInt();
    searchResult.hasSav = qry.value(6).toInt();
    searchResult.ID = qry.value(1).toString();
    searchResult.manager = qry.value(3).toInt();
    searchResult.isTrail = qry.value(8).toInt();
    searchResult.passWord = qry.value(2).toString();
    searchResult.maintPers = qry.value(9).toInt();

    return searchResult;
}

