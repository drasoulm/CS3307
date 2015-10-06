#-------------------------------------------------
#
# Project created by QtCreator 2015-09-22T13:59:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQLite_DB
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    managerlogin.cpp \
    createuser.cpp \
    deleteuser.cpp \
    allcustomersview.cpp \
    customerlog.cpp \
    clientview.cpp \
    maintanenceview.cpp \
    helper.cpp

HEADERS  += mainwindow.h \
    managerlogin.h \
    createuser.h \
    deleteuser.h \
    allcustomersview.h \
    customerlog.h \
    clientview.h \
    maintanenceview.h \
    helper.h

FORMS    += mainwindow.ui \
    managerlogin.ui \
    createuser.ui \
    deleteuser.ui \
    allcustomersview.ui \
    clientview.ui \
    maintanenceview.ui
