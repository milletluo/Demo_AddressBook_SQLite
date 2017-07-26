#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T08:23:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AddressBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    friendmanager.cpp

HEADERS  += mainwindow.h \
    friendmanager.h

FORMS    += mainwindow.ui \
    friendmanager.ui
