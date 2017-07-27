#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T08:23:20
#
#-------------------------------------------------

QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AddressBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    friendmanager.cpp \
    addstudlg.cpp

HEADERS  += mainwindow.h \
    friendmanager.h \
    addstudlg.h

FORMS    += mainwindow.ui \
    friendmanager.ui \
    addstudlg.ui
