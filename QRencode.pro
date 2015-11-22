#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T13:22:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRencode
TEMPLATE = app


SOURCES += main.cpp\
    maindialog.cpp

HEADERS  += \
    maindialog.h

# INCLUDEPATH += libs
LIBS += -lqrencode

FORMS += \
    maindialog.ui
