#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T14:38:31
#
#-------------------------------------------------

QT       += core gui
QT  += widgets

LIBS += -LC:\mymysql\mysql\lib -llibmysql

TARGET = cdma
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindlg.cpp \
    scriptdlg.cpp \
    mymysql.cpp

HEADERS  += mainwindow.h \
    logindlg.h \
    scriptdlg.h \
    mymysql.h

RESOURCES += \
    cdma.qrc
