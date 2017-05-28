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
    QMenu *dataMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;
    QAction *loginAction;
    QAction *logoutAction;
    QAction *exitAction;

    QAction *insert_mscAction;

    QAction *select_mscAction;


    QAction *insert_cellAction;
    QAction *insert_bscAction;
    QAction *delete_cellAction;
    QAction *delete_bscAction;
    QAction *delete_mscAction;
    QAction *select_cellAction;
    QAction *select_bscAction;
    QAction *update_cellAction;
    QAction *update_bscAction;
    QAction *update_mscAction;

    QAction *scriptAction;

    QAction *cascadeAction;
    QAction *tileAction;

private slots:
    void on_login();
    void on_logout();
    void on_exit();

    void on_script();

    void on_selectMSC();
    void on_select_cell();
    void on_select_bsc();

    void on_insert_msc();
    void on_insert_cell();
    void on_insert_bsc();

     void on_delete_cell();
     void on_delete_bsc();
     void on_delete_msc();

     void on_update_cell();
     void on_update_bsc();
     void on_update_msc();

    void cascadeSubWindows();
    void tileSubWindows();
};

#endif // MAINWINDOW_H
