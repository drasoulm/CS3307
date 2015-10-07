#include "customerlog.h"
#include "ctime"
#include "mainwindow.h"

customerLog::customerLog()
{

}

void customerLog::createCustomerLogFile(){
    MainWindow mw;
    if(!mw.fileExists("Action.log")){
        QFile file("Action.log");
        file.open(QIODevice::ReadWrite);
    }else{

        qDebug()<<("FILE EXISTS");

    }
}



void customerLog::customerActionToLog(QString action){
    ofstream file;
    file.open("Action.log",ios_base::app);
    file << now();
    file << ":";
    file << action.toStdString();
    file << endl;
    file << endl;
}

void customerLog::addClientToLog(QString name, QString userName, QString role){

    /*This is only called once when the client logs in. It's for readibility as the log will have all clients/managers seperated by -------- */
    std::string log = now() + std::string(":") + name.toStdString() + std::string(",") + userName.toStdString() + std::string(" - LOGGED IN AS: ") + role.toStdString();
    ofstream file;
    file.open("Action.log", ios_base::app);
    file<< "------------------------------------------" << endl;
    file << log <<endl << endl;


}

string customerLog::now(){
    time_t t;
    struct tm * now;
    char buffer[80];

    t = time(&t);
    now = localtime(&t);
    strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", now);
    std::string currentDate(buffer);

    return currentDate;
}

