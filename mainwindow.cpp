#include "mainwindow.h"
#include "scriptdlg.h"
#include "select_mscdlg.h"
#include "insert_mscdlg.h"

#include <QTextCodec>
#include <QMessageBox>
#include <QCloseEvent>
#include <QStandardItemModel>
#include <QTableView>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    QTextCodec *codec = QTextCodec::codecForName("system");
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForTr(codec);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));


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
    adminMenu->addAction(insert_mscAction);
    adminMenu->addAction(select_mscAction);
    adminMenu->addSeparator();
    adminMenu->addAction(scriptAction);

    adminMenu = menuBar()->addMenu(tr("����"));
    adminMenu->addAction(cascadeAction);
    adminMenu->addAction(tileAction);

    adminMenu = menuBar()->addMenu(tr("����"));
}

void MainWindow::createActions()
{
    loginAction = new QAction(tr("��¼"), this);
    loginAction->setShortcut(tr("Ctrl+u"));
    connect(loginAction, SIGNAL(triggered()), this, SLOT(on_login()));

    logoutAction = new QAction(tr("ע��"), this);
    logoutAction->setShortcut(tr("Ctrl+b"));
    connect(logoutAction, SIGNAL(triggered()), this, SLOT(on_logout()));

    exitAction = new QAction(tr("�˳�"), this);
    exitAction->setShortcut(tr("ctrl+w"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(on_exit()));

    insert_mscAction = new QAction(tr("���MSC"), this);
    insert_mscAction->setShortcut(tr("Ctrl+F"));
    connect(insert_mscAction, SIGNAL(triggered()), this, SLOT(on_insert_msc()));

    select_mscAction = new QAction(tr("��ѯMSC"), this);
    select_mscAction->setShortcut(tr("Ctrl+L"));
    connect(select_mscAction, SIGNAL(triggered()), this, SLOT(on_selectMSC()));

    scriptAction = new QAction(tr("ִ�нű�"), this);
    scriptAction->setShortcut(tr("Ctrl+p"));
    scriptAction->setEnabled(false);
    connect(scriptAction,SIGNAL(triggered()), this, SLOT(on_script()));

    cascadeAction = new QAction(tr("���"), this);
    cascadeAction->setShortcut(tr("Ctrl+Q"));
    connect(cascadeAction, SIGNAL(triggered()), this, SLOT(cascadeSubWindows()));

    tileAction = new QAction(tr("����"), this);
    tileAction->setShortcut(tr("Ctrl+T"));
    connect(tileAction, SIGNAL(triggered()), this, SLOT(tileSubWindows()));
}

void MainWindow::on_login()
{
    //QMessageBox::information(this, tr("success"), tr("ok"), QMessageBox::Ok);
    logindlg dlg;
    dlg.exec();

    if(dlg.islogin)
    {
        int res = db.sql_connect(dlg.hostip.toStdString().data(),
                                 dlg.userid.toStdString().data(),
                                 dlg.passwd.toStdString().data(),
                                 dlg.dbname.toStdString().data());
        if(res == -1)
        {
            QMessageBox::information(this, tr("��¼ʧ��"), db.geterror());
        }else
        {
            QMessageBox::information(this, "", tr("��¼�ɹ�"));
            scriptAction->setEnabled(true);
        }
    }
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

void MainWindow::on_exit()
{
    close();
}

void MainWindow::on_logout()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, tr("��ʾ"),
                                                               tr("�Ƿ�ע��"),
                                                               QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::Yes)
    {
        db.sql_disconnect();
        scriptAction->setEnabled(false);
    }
}

void MainWindow::on_script()
{
    scriptDlg dlg;
    dlg.exec();
    //showview();

    //��д�����ʱ���Ȳ���
//    if(db.sql_exec("delete from table1 where class = 'C++'") == -1)
//        QMessageBox::information(this, "execʧ��", db.geterror());//geterror()���ٴ��ڵ���
//    else
//        QMessageBox::information(this, "", "exec�ɹ�");
    if(dlg.islogin)
    {
        script_msg(dlg.SQL.toStdString().data());
    }
}

//ִ��SQL��䣬��ִ�з���ֵ����QStandardItemModel,ͨ��QTableView��ʾ����
void MainWindow::script_msg(const char * SQL)
{
//    const char *src = SQL.toStdString().data();
//    if((strncmp(src, "SELECT", 6) == 0) || (strncmp(src, "select", 6) == 0)
//            || (strncmp(src, "show", 4) == 0) || (strncmp(src, "SHOW", 4) == 0)
//            || (strncmp(src, "DESC", 4) == 0) || (strncmp(src, "desc", 4) == 0))
//    //���src�з������ݼ�SQL��䣬��ô����sql_open����
//    {
//        QStandardItemModel *modul = NULL;
//        if(db.sql_open(SQL.toStdString().data(), &modul) == 0)
//        {
//            QTableView *view1 = new QTableView;
//            view1->setAttribute(Qt::WA_DeleteOnClose);
//            view1->setModel(modul);
//            mdiarea->addSubWindow(view1);
//            view1->setStyleSheet("border-image: url(:/icon/3.jpg);");

//            view1->setWindowTitle(tr("��ѯ�����ʾ����"));
//            //view1 �̳���widget�����û��module����ôview������ʾ�κζ���

//            view1->show();
//            mdiarea->activeSubWindow()->resize(width() - 100, height() - 100);
//        }else
//        {
//            QMessageBox::information(this, tr("����"), db.geterror());
//        }
//    }
//    else
//    {
//        if(db.sql_exec(SQL.toStdString().data()) == 0)
//        {
//            QMessageBox::information(this, tr("��ʾ"), tr("ִ�гɹ�"));
//        }
//        else
//        {
//            QMessageBox::information(this, tr("ִ��ʧ��"), db.geterror());
//        }
//    }

    int res = 0;
    if((strncmp(SQL, "SELECT", 6) == 0) || (strncmp(SQL, "select", 6) == 0)
                || (strncmp(SQL, "show", 4) == 0) || (strncmp(SQL, "SHOW", 4) == 0)
                || (strncmp(SQL, "DESC", 4) == 0) || (strncmp(SQL, "desc", 4) == 0))
    {
        QStandardItemModel *modul = NULL;
        res = db.sql_open(SQL, &modul);//�����selectִ�����

        QTableView *view = new QTableView;
        view->setAttribute(Qt::WA_DeleteOnClose);//view��closeʱ���Զ�delete
        mdiarea->addSubWindow(view);
        //view->setStyleSheet("border-image: url(3.jpg);");
        view->setStyleSheet("border-image: url(:/icon/3.jpg);");

        view->setModel(modul);
        view->show();
        mdiarea->activeSubWindow()->resize(width() - 100, height() - 100);
    }
    else
        res = db.sql_exec(SQL);

    if(res == -1 )
        QMessageBox::information(this, tr("execʧ��"), db.geterror());//geterror()���ٴ��ڵ���
    else
        QMessageBox::information(this, "", tr("exec�ɹ�"));
}


void MainWindow::showview()
{
    QStandardItemModel *model = new QStandardItemModel(5, 3);//����һ��5��3�е�

    //����module����ͷ����
    model->setHeaderData(0, Qt::Horizontal, "����");
    model->setHeaderData(1, Qt::Horizontal, "�Ա�");
    model->setHeaderData(2, Qt::Horizontal, "����");

    QTableView *view1 = new QTableView;
    view1->setAttribute(Qt::WA_DeleteOnClose);
    //view1��close��ʱ���Զ�delete�����ʱ�������module�Ļ������module�ᱻview�Զ��ͷ�
    mdiarea->addSubWindow(view1);
    view1->setStyleSheet("border-image: url(:/icon/3.jpg);");

    //view1�̳���widget�����û��module����ôview������ʾ�κ�����
    view1->setModel(model);
    view1->show();
    mdiarea->activeSubWindow()->resize(width() - 100, height() - 100);

}

void MainWindow::cascadeSubWindows()
{
    mdiarea->cascadeSubWindows();
}

void MainWindow::tileSubWindows()
{
    mdiarea->tileSubWindows();
}

void MainWindow::on_selectMSC()
{
    //----------������ѯMSC�Ի���--------------------------
    select_mscDlg select_msc(this);
    select_msc.resize(400, 200);
    select_msc.exec();


    if(select_msc.isok)
    {
        script_msg(select_msc.SQL.toStdString().data());
    }
}

void MainWindow::on_insert_msc()
{
    insert_mscDlg insert_msc(this);
    insert_msc.resize(400, 200);
    insert_msc.exec();

    if(insert_msc.isok)//����û����ȷ����ť
    {
        script_msg(insert_msc.SQL.toStdString().data());
    }
}

