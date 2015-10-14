#include <QApplication>
#include "mainwindow.h"
#include "customerlog.h"


int main(int argc, char *argv[])
{

    /*This comment is to see if git works*/
    QApplication a(argc, argv);

    MainWindow w;

    customerLog logFile;

    //Create necessary database
    if(w.fileExists("database.db")){

    }else{
        //create file then run query for table
        w.createDBFileThenTable();
    }

    //create Execution Trace File
    logFile.createCustomerLogFile();

    w.show();


    return a.exec();
}
