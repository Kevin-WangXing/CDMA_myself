#include "mainwindow.h"

#include <QTextCodec>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTextCodec *codec = QTextCodec::codecForName("system");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    setWindowTitle(tr("CDMA无线基站管理系统"));
    setWindowIcon(QIcon(":/icon/main.png"));

    mdiarea = new QMdiArea;
    setCentralWidget(mdiarea);
    mdiarea->setBackground(Qt::NoBrush);
    //setBackgroundRole(Qt::NoBrush);
    mdiarea->setStyleSheet("background-image: url(:/icon/1.jpg);");//根据窗口大小自动调整加载的图片大小
    //setStyleSheet("border-image: url(:/icon/1.jpg);");//一张图片，自动适应屏幕
    mdiarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiarea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    createActions();
    createMenus();

}

MainWindow::~MainWindow()
{

}
//菜单栏
void MainWindow::createMenus()
{
    adminMenu = menuBar()->addMenu(tr("管理"));
    adminMenu->addAction(loginAction);
    adminMenu->addAction(logoutAction);
    adminMenu->addSeparator();
    adminMenu->addAction(exitAction);

    adminMenu = menuBar()->addMenu(tr("数据"));

    adminMenu = menuBar()->addMenu(tr("窗口"));

    adminMenu = menuBar()->addMenu(tr("帮助"));
}

void MainWindow::createActions()
{
    loginAction = new QAction(tr("登录"), this);
    loginAction->setShortcut(tr("Ctrl+u"));
    connect(loginAction, SIGNAL(triggered()), this, SLOT(on_login()));

    logoutAction = new QAction(tr("注销"), this);
    logoutAction->setShortcut(tr("Ctrl+b"));
    connect(logoutAction, SIGNAL(triggered()), this, SLOT(on_login()));

    exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(tr("ctrl+w"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(on_logout()));
}

void MainWindow::on_login()
{
    //QMessageBox::information(this, tr("success"), tr("ok"), QMessageBox::Ok);
    logindlg dlg;
    dlg.exec();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    QMessageBox::StandardButton button = QMessageBox::question(this, tr("提示"),
                                                               tr("是否退出程序"),
                                                               QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::Yes)
        e->accept();
    else
        e->ignore();
}

void MainWindow::on_logout()
{
    close();
}
