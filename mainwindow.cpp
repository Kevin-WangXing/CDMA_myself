
#include "mainwindow.h"
#include "scriptdlg.h"
#include "select_mscdlg.h"
#include "select_bscdlg.h"
#include "select_celldlg.h"
#include "update_bscdlg.h"
#include "update_celldlg.h"
#include "update_mscdlg.h"
#include "delete_bscdlg.h"
#include "delete_celldlg.h"
#include "delete_mscdlg.h"
#include "insert_mscdlg.h"
#include "insert_bscdlg.h"
#include "insert_celldlg.h"

#include <QTextCodec>
#include <QMessageBox>
#include <QCloseEvent>
#include <QStandardItemModel>
#include <QTableView>
#include <QMdiSubWindow>
#include <QInputDialog>

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

    dataMenu = menuBar()->addMenu(tr("数据"));
    dataMenu->addAction(insert_mscAction);
    dataMenu->addAction(insert_bscAction);//在数据菜单下加入添加基站控制器行为
    dataMenu->addAction(insert_mscAction);//在数据菜单下加入添加MSC行为
    dataMenu->addAction(delete_cellAction);//在数据菜单下加入删除基站行为
    dataMenu->addAction(delete_bscAction);//在数据菜单下加入删除基站控制器行为
    dataMenu->addAction(delete_mscAction);//在数据菜单下加入删除MSC行为
    dataMenu->addAction(select_cellAction);//在数据菜单下加入查询基站行为
    dataMenu->addAction(select_bscAction);//在数据菜单下加入查询基站控制器行为
    dataMenu->addAction(select_mscAction);//在数据菜单下加入查询MSC行为
    dataMenu->addAction(update_cellAction);//在数据菜单下加入修改基站行为
    dataMenu->addAction(update_bscAction);//在数据菜单下加入修改基站控制器行为
    dataMenu->addAction(update_mscAction);//在数据菜单下加入修改MSC行为
    dataMenu->addSeparator();
    dataMenu->addAction(scriptAction);

    windowMenu = menuBar()->addMenu(tr("窗口"));
    windowMenu->addAction(cascadeAction);
    windowMenu->addAction(tileAction);

    helpMenu = menuBar()->addMenu(tr("帮助"));
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

    insert_cellAction = new QAction(tr("添加基站"), this);
    insert_cellAction->setShortcut(tr("Ctrl+d"));
    insert_cellAction->setEnabled(false);
    connect(insert_cellAction, SIGNAL(triggered()), this, SLOT(on_insert_cell()));

    insert_bscAction = new QAction(tr("添加基站控制器"), this);
    insert_bscAction->setShortcut(tr("Ctrl+e"));
    insert_bscAction->setEnabled(false);
    connect(insert_bscAction, SIGNAL(triggered()), this, SLOT(on_insert_bsc()));

    insert_mscAction = new QAction(tr("添加MSC"), this);
    insert_mscAction->setShortcut(tr("Ctrl+F"));
    insert_mscAction->setEnabled(false);
    connect(insert_mscAction, SIGNAL(triggered()), this, SLOT(on_insert_msc()));

    delete_cellAction = new QAction(tr("删除基站"), this);
    delete_cellAction->setShortcut(tr("Ctrl+g"));
    delete_cellAction->setEnabled(false);
    connect(delete_cellAction, SIGNAL(triggered()), this, SLOT(on_delete_cell()));

    delete_bscAction = new QAction(tr("删除基站控制器"), this);
    delete_bscAction->setShortcut(tr("Ctrl+h"));
    delete_bscAction->setEnabled(false);
    connect(delete_bscAction, SIGNAL(triggered()), this, SLOT(on_delete_bsc()));
    delete_mscAction = new QAction(tr("删除MSC"), this);
    delete_mscAction->setShortcut(tr("Ctrl+i"));
    delete_mscAction->setEnabled(false);
    connect(delete_mscAction, SIGNAL(triggered()), this, SLOT(on_delete_msc()));

    select_cellAction = new QAction(tr("查询基站"), this);
    select_cellAction->setShortcut(tr("Ctrl+j"));
    select_cellAction->setEnabled(false);
    connect(select_cellAction, SIGNAL(triggered()), this, SLOT(on_select_cell()));

    select_bscAction = new QAction(tr("查询基站控制器"), this);
    select_bscAction->setShortcut(tr("Ctrl+k"));
    select_bscAction->setEnabled(false);
    connect(select_bscAction, SIGNAL(triggered()), this, SLOT(on_select_bsc()));

    select_mscAction = new QAction(tr("查询MSC"), this);
    select_mscAction->setShortcut(tr("Ctrl+L"));
    select_mscAction->setEnabled(false);
    connect(select_mscAction, SIGNAL(triggered()), this, SLOT(on_selectMSC()));

    update_cellAction = new QAction(tr("修改基站"), this);
    update_cellAction->setShortcut(tr("Ctrl+m"));
    update_cellAction->setEnabled(false);
    connect(update_cellAction, SIGNAL(triggered()), this, SLOT(on_update_cell()));

    update_bscAction = new QAction(tr("修改基站控制器"), this);
    update_bscAction->setShortcut(tr("Ctrl+n"));
    update_bscAction->setEnabled(false);
    connect(update_bscAction, SIGNAL(triggered()), this, SLOT(on_update_bsc()));

    update_mscAction = new QAction(tr("修改MSC"), this);
    update_mscAction->setShortcut(tr("Ctrl+o"));
    update_mscAction->setEnabled(false);
    connect(update_mscAction, SIGNAL(triggered()), this, SLOT(on_update_msc()));

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
            insert_cellAction->setEnabled(true);
            insert_bscAction->setEnabled(true);
            insert_mscAction->setEnabled(true);
            delete_cellAction->setEnabled(true);
            delete_bscAction->setEnabled(true);
            delete_mscAction->setEnabled(true);
            select_cellAction->setEnabled(true);
            select_bscAction->setEnabled(true);
            select_mscAction->setEnabled(true);
            update_cellAction->setEnabled(true);
            update_bscAction->setEnabled(true);
            update_mscAction->setEnabled(true);
            db.sql_exec("set names utf8");//设置数据库连接为uft8字符集
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
        scriptAction->setEnabled(false);//设置行为不可用
        insert_cellAction->setEnabled(false);
        insert_bscAction->setEnabled(false);
        insert_mscAction->setEnabled(false);
        delete_cellAction->setEnabled(false);
        delete_bscAction->setEnabled(false);
        delete_mscAction->setEnabled(false);
        select_cellAction->setEnabled(false);
        select_bscAction->setEnabled(false);
        select_mscAction->setEnabled(false);
        update_cellAction->setEnabled(false);
        update_bscAction->setEnabled(false);
        update_mscAction->setEnabled(false);
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

void MainWindow::on_select_cell()
{
    //-------------弹出查询cell对话框------------------------------
    select_cellDlg select_cell(this);
    select_cell.resize(400, 200);
    select_cell.exec();

    if(select_cell.isok)//如果用户点击确定按钮
    {
        script_msg(select_cell.SQL.toStdString().data());
    }
}

void MainWindow::on_select_bsc()
{
    //-------------弹出查询基站控制器对话框------------------------------
    select_bscDlg select_bsc(this);
    select_bsc.resize(400, 200);
    select_bsc.exec();

    if(select_bsc.isok)//如果用户点击确定按钮
    {
        script_msg(select_bsc.SQL.toStdString().data());
    }
}

void MainWindow::on_insert_cell()
{
    //-------------弹出添加基站对话框------------------------------
    insert_cellDlg insert_cell(this);
    insert_cell.resize(400, 200);
    insert_cell.exec();

    if(insert_cell.isok)//如果用户点击确定按钮
    {
        script_msg(insert_cell.SQL.toStdString().data());
    }
}

void MainWindow::on_insert_bsc()
{
    //-------------弹出添加基站对话框------------------------------
    insert_bscDlg insert_bsc(this);
    insert_bsc.resize(400, 200);
    insert_bsc.exec();

    if(insert_bsc.isok)//如果用户点击确定按钮
    {
        script_msg(insert_bsc.SQL.toStdString().data());
    }
}

void MainWindow::on_delete_cell()
{
    //-------------弹出删除cell对话框------------------------------
    delete_cellDlg delete_cell(this);
    delete_cell.resize(400, 200);
    delete_cell.exec();

    if(delete_cell.isok)//如果用户点击确定按钮
    {
        script_msg(delete_cell.SQL.toStdString().data());
    }
}

void MainWindow::on_delete_bsc()
{
    //-------------弹出删除MSC对话框------------------------------
    delete_bscDlg delete_bsc(this);
    delete_bsc.resize(400, 200);
    delete_bsc.exec();

    if(delete_bsc.isok)//如果用户点击确定按钮
    {
        script_msg(delete_bsc.SQL.toStdString().data());
    }
}

void MainWindow::on_delete_msc()
{
    //-------------弹出删除MSC对话框------------------------------
    delete_mscDlg delete_msc(this);
    delete_msc.resize(400, 200);
    delete_msc.exec();

    if(delete_msc.isok)//如果用户点击确定按钮
    {
        script_msg(delete_msc.SQL.toStdString().data());
    }
}
void MainWindow::on_update_cell()
{
    //-------------弹出修改基站对话框------------------------------
    bool isok =  false;
    QString cellid = QInputDialog::getText(this, tr("输入"), tr("输入要修改的基站ID"), QLineEdit::Normal, tr(""), &isok);

    if(isok)
    {
        QString SQL = QString("select cellid, cellname, bscid, DATE_FORMAT(createdate, '%Y-%m-%d'), longitude, latitude, description from cells where cellid = %1").arg(cellid);
        QStringList list;
        db.sql_open_str(SQL.toStdString().data(), list);
        if (list.count() < 7)
        {
            QMessageBox::information(this, tr("错误"), tr("没有此基站ID"));
            return;
        }
        //-------------弹出修改对话框------------------------------

        update_cellDlg update_cell(list[0], list[1], list[2], list[3], list[4], list[5], list[6], this);
        update_cell.resize(400, 200);
        update_cell.exec();

        if(update_cell.isok)//如果用户点击确定按钮
        {
            script_msg(update_cell.SQL.toStdString().data());
        }
    }
}

void MainWindow::on_update_bsc()
{
    //-------------弹出修改基站控制器对话框------------------------------
    bool isok =  false;
    QString bscid = QInputDialog::getText(this, tr("输入"), tr("输入要修改的基站控制器ID"), QLineEdit::Normal, tr(""), &isok);

    if(isok)
    {
        QString SQL = QString("select bscid, bscpc, bscname, mscid, branchname, DATE_FORMAT(createdate, '%Y-%m-%d'), description from bscs where bscid = %1").arg(bscid);
        QMessageBox::information(this, "list", SQL);

        QStringList list;
        db.sql_open_str(SQL.toStdString().data(), list);
        if (list.count() < 7)
        {
            QMessageBox::information(this, tr("错误"), tr("没有此基站控制器ID"));
            return;
        }
        //-------------弹出修改对话框------------------------------

        update_bscDlg update_bsc(list[0], list[1], list[2], list[3], list[4], list[5], list[6], this);
        update_bsc.resize(400, 200);
        update_bsc.exec();

        if(update_bsc.isok)//
        {
            script_msg(update_bsc.SQL.toStdString().data());
        }
    }
}

void MainWindow::on_update_msc()
{
    //-------------弹出修改MSC对话框------------------------------
    bool isok =  false;
    QString mscid = QInputDialog::getText(this, tr("输入"), tr("输入要修改的MSCID"), QLineEdit::Normal, tr(""), &isok);

    if(isok)
    {
        QString SQL = QString("select mscid, mscpc, mscname, districtname, DATE_FORMAT(createdate, '%Y-%m-%d'), description from mscs where mscid = %1").arg(mscid);
        QStringList list;
        db.sql_open_str(SQL.toStdString().data(), list);
        if (list.count() < 6)
        {
            QMessageBox::information(this, tr("错误"), tr("没有此MSCID"));
            return;
        }
        //-------------弹出修改对话框------------------------------

        update_mscDlg update_msc(list[0], list[1], list[2], list[3], list[4], list[5], this);
        update_msc.resize(400, 200);
        update_msc.exec();

        if(update_msc.isok)//
        {
            script_msg(update_msc.SQL.toStdString().data());
        }
    }
}


