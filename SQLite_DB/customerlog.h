#ifndef CUSTOMERLOG_H
#define CUSTOMERLOG_H

#include "QString"
#include <ctime>
#include <iostream>
#include <fstream>
#include "mainwindow.h"

using namespace std;

class customerLog
{
public:
    customerLog();


    void createCustomerLogFile();
    void customerActionToLog(QString action);
    void addClientToLog(QString name, QString userName, QString role);
    string now();

};

#endif // CUSTOMERLOG_H
