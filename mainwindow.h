#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMdiArea>
#include <QAction>

#include "logindlg.h"
#include "mymysql.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
        void closeEvent(QCloseEvent *e);

private:
    mymysql db;

    void createMenus();
    void createActions();

    void showview();
    void script_msg(const char *SQL);

private:


    QMdiArea *mdiarea;

    QMenu *adminMenu;
    QAction *loginAction;
    QAction *logoutAction;
    QAction *exitAction;

    QAction *insert_mscAction;
    QAction *select_mscAction;
    QAction *scriptAction;

    QAction *cascadeAction;
    QAction *tileAction;

private slots:
    void on_login();
    void on_logout();
    void on_exit();

    void on_script();

    void on_selectMSC();

    void on_insert_msc();

    void cascadeSubWindows();
    void tileSubWindows();
};

#endif // MAINWINDOW_H
