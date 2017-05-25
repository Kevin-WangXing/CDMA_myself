#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMdiArea>
#include <QAction>

#include "logindlg.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void closeEvent(QCloseEvent *e);

    void createMenus();
    void createActions();

private:


    QMdiArea *mdiarea;

    QMenu *adminMenu;
    QAction *loginAction;
    QAction *logoutAction;
    QAction *exitAction;

private slots:
    void on_login();
    void on_logout();
};

#endif // MAINWINDOW_H
