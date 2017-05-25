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

    setWindowTitle(tr("CDMA���߻�վ����ϵͳ"));
    setWindowIcon(QIcon(":/icon/main.png"));

    mdiarea = new QMdiArea;
    setCentralWidget(mdiarea);
    mdiarea->setBackground(Qt::NoBrush);
    //setBackgroundRole(Qt::NoBrush);
    mdiarea->setStyleSheet("background-image: url(:/icon/1.jpg);");//���ݴ��ڴ�С�Զ��������ص�ͼƬ��С
    //setStyleSheet("border-image: url(:/icon/1.jpg);");//һ��ͼƬ���Զ���Ӧ��Ļ
    mdiarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiarea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    createActions();
    createMenus();

}

MainWindow::~MainWindow()
{

}
//�˵���
void MainWindow::createMenus()
{
    adminMenu = menuBar()->addMenu(tr("����"));
    adminMenu->addAction(loginAction);
    adminMenu->addAction(logoutAction);
    adminMenu->addSeparator();
    adminMenu->addAction(exitAction);

    adminMenu = menuBar()->addMenu(tr("����"));

    adminMenu = menuBar()->addMenu(tr("����"));

    adminMenu = menuBar()->addMenu(tr("����"));
}

void MainWindow::createActions()
{
    loginAction = new QAction(tr("��¼"), this);
    loginAction->setShortcut(tr("Ctrl+u"));
    connect(loginAction, SIGNAL(triggered()), this, SLOT(on_login()));

    logoutAction = new QAction(tr("ע��"), this);
    logoutAction->setShortcut(tr("Ctrl+b"));
    connect(logoutAction, SIGNAL(triggered()), this, SLOT(on_login()));

    exitAction = new QAction(tr("�˳�"), this);
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
    QMessageBox::StandardButton button = QMessageBox::question(this, tr("��ʾ"),
                                                               tr("�Ƿ��˳�����"),
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
