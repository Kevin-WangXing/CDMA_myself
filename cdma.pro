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
    mymysql.cpp \
    select_mscdlg.cpp \
    insert_mscdlg.cpp \
    delete_bscdlg.cpp \
    delete_celldlg.cpp \
    delete_mscdlg.cpp \
    insert_bscdlg.cpp \
    insert_celldlg.cpp \
    select_bscdlg.cpp \
    select_celldlg.cpp \
    update_bscdlg.cpp \
    update_celldlg.cpp \
    update_mscdlg.cpp

HEADERS  += mainwindow.h \
    logindlg.h \
    scriptdlg.h \
    mymysql.h \
    select_mscdlg.h \
    insert_mscdlg.h \
    delete_bscdlg.h \
    delete_celldlg.h \
    delete_mscdlg.h \
    insert_bscdlg.h \
    insert_celldlg.h \
    select_bscdlg.h \
    select_celldlg.h \
    update_bscdlg.h \
    update_celldlg.h \
    update_mscdlg.h

RESOURCES += \
    cdma.qrc
