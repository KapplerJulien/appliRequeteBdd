#-------------------------------------------------
#
# Project created by QtCreator 2017-02-27T09:31:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = appliRequeteBdd
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogconnection.cpp \
    dialogabout.cpp

HEADERS  += mainwindow.h \
    dialogconnection.h \
    dialogabout.h

FORMS    += mainwindow.ui \
    dialogconnection.ui \
    dialogabout.ui

TRANSLATIONS += appliRequeteBdd_fr_FR.ts
