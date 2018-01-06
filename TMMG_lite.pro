#-------------------------------------------------
#
# Project created by QtCreator 2015-01-09T17:30:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TMMG_lite
TEMPLATE = app
VERSION = 1.0.1
QMAKE_TARGET_COPYRIGHT = Raymond
win32:RC_ICONS += tmicon.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    QProgressIndicator.cpp

HEADERS  += mainwindow.h \
    defines.h \
    QProgressIndicator.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
