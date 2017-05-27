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
    adminMenu->addAction(insert_mscAction);
    adminMenu->addAction(select_mscAction);
    adminMenu->addSeparator();
    adminMenu->addAction(scriptAction);

    adminMenu = menuBar()->addMenu(tr("窗口"));
    adminMenu->addAction(cascadeAction);
    adminMenu->addAction(tileAction);

    adminMenu = menuBar()->addMenu(tr("帮助"));
}

void MainWindow::createActions()
{
    loginAction = new QAction(tr("登录"), this);
    loginAction->setShortcut(tr("Ctrl+u"));
    connect(loginAction, SIGNAL(triggered()), this, SLOT(on_login()));

    logoutAction = new QAction(tr("注销"), this);
    logoutAction->setShortcut(tr("Ctrl+b"));
    connect(logoutAction, SIGNAL(triggered()), this, SLOT(on_logout()));

    exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(tr("ctrl+w"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(on_exit()));

    insert_mscAction = new QAction(tr("添加MSC"), this);
    insert_mscAction->setShortcut(tr("Ctrl+F"));
    connect(insert_mscAction, SIGNAL(triggered()), this, SLOT(on_insert_msc()));

    select_mscAction = new QAction(tr("查询MSC"), this);
    select_mscAction->setShortcut(tr("Ctrl+L"));
    connect(select_mscAction, SIGNAL(triggered()), this, SLOT(on_selectMSC()));

    scriptAction = new QAction(tr("执行脚本"), this);
    scriptAction->setShortcut(tr("Ctrl+p"));
    scriptAction->setEnabled(false);
    connect(scriptAction,SIGNAL(triggered()), this, SLOT(on_script()));

    cascadeAction = new QAction(tr("层叠"), this);
    cascadeAction->setShortcut(tr("Ctrl+Q"));
    connect(cascadeAction, SIGNAL(triggered()), this, SLOT(cascadeSubWindows()));

    tileAction = new QAction(tr("并列"), this);
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
            QMessageBox::information(this, tr("登录失败"), db.geterror());
        }else
        {
            QMessageBox::information(this, "", tr("登录成功"));
            scriptAction->setEnabled(true);
        }
    }
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

void MainWindow::on_exit()
{
    close();
}

void MainWindow::on_logout()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, tr("提示"),
                                                               tr("是否注销"),
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

    //在写代码的时间先测试
//    if(db.sql_exec("delete from table1 where class = 'C++'") == -1)
//        QMessageBox::information(this, "exec失败", db.geterror());//geterror()减少窗口弹出
//    else
//        QMessageBox::information(this, "", "exec成功");
    if(dlg.islogin)
    {
        script_msg(dlg.SQL.toStdString().data());
    }
}

//执行SQL语句，将执行返回值放入QStandardItemModel,通过QTableView显示出来
void MainWindow::script_msg(const char * SQL)
{
//    const char *src = SQL.toStdString().data();
//    if((strncmp(src, "SELECT", 6) == 0) || (strncmp(src, "select", 6) == 0)
//            || (strncmp(src, "show", 4) == 0) || (strncmp(src, "SHOW", 4) == 0)
//            || (strncmp(src, "DESC", 4) == 0) || (strncmp(src, "desc", 4) == 0))
//    //如果src有返回数据集SQL语句，那么调用sql_open函数
//    {
//        QStandardItemModel *modul = NULL;
//        if(db.sql_open(SQL.toStdString().data(), &modul) == 0)
//        {
//            QTableView *view1 = new QTableView;
//            view1->setAttribute(Qt::WA_DeleteOnClose);
//            view1->setModel(modul);
//            mdiarea->addSubWindow(view1);
//            view1->setStyleSheet("border-image: url(:/icon/3.jpg);");

//            view1->setWindowTitle(tr("查询结果显示窗口"));
//            //view1 继承自widget，如果没有module，那么view不会显示任何东西

//            view1->show();
//            mdiarea->activeSubWindow()->resize(width() - 100, height() - 100);
//        }else
//        {
//            QMessageBox::information(this, tr("错误"), db.geterror());
//        }
//    }
//    else
//    {
//        if(db.sql_exec(SQL.toStdString().data()) == 0)
//        {
//            QMessageBox::information(this, tr("提示"), tr("执行成功"));
//        }
//        else
//        {
//            QMessageBox::information(this, tr("执行失败"), db.geterror());
//        }
//    }

    int res = 0;
    if((strncmp(SQL, "SELECT", 6) == 0) || (strncmp(SQL, "select", 6) == 0)
                || (strncmp(SQL, "show", 4) == 0) || (strncmp(SQL, "SHOW", 4) == 0)
                || (strncmp(SQL, "DESC", 4) == 0) || (strncmp(SQL, "desc", 4) == 0))
    {
        QStandardItemModel *modul = NULL;
        res = db.sql_open(SQL, &modul);//如果是select执行这个

        QTableView *view = new QTableView;
        view->setAttribute(Qt::WA_DeleteOnClose);//view在close时间自动delete
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
        QMessageBox::information(this, tr("exec失败"), db.geterror());//geterror()减少窗口弹出
    else
        QMessageBox::information(this, "", tr("exec成功"));
}


void MainWindow::showview()
{
    QStandardItemModel *model = new QStandardItemModel(5, 3);//建立一个5行3列的

    //设置module的列头名称
    model->setHeaderData(0, Qt::Horizontal, "姓名");
    model->setHeaderData(1, Qt::Horizontal, "性别");
    model->setHeaderData(2, Qt::Horizontal, "年龄");

    QTableView *view1 = new QTableView;
    view1->setAttribute(Qt::WA_DeleteOnClose);
    //view1在close的时候自动delete，这个时候如果有module的话，这个module会被view自动释放
    mdiarea->addSubWindow(view1);
    view1->setStyleSheet("border-image: url(:/icon/3.jpg);");

    //view1继承自widget，如果没有module，那么view不会显示任何数据
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
    //----------弹出查询MSC对话框--------------------------
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

    if(insert_msc.isok)//如果用户点击确定按钮
    {
        script_msg(insert_msc.SQL.toStdString().data());
    }
}

