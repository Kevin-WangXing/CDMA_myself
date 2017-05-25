#include "logindlg.h"

#include <QGridLayout>
#include <QPalette>
#include <QMessageBox>

logindlg::logindlg()
{
    setWindowTitle(tr("登录"));
    islogin = false;
    label0 = new QLabel(tr("用户名"));
    label1 = new QLabel(tr("密码"));
    label2 = new QLabel(tr("数据库名称"));
    label3 = new QLabel(tr("服务器IP"));

    lineEditUserID = new QLineEdit;
    lineEditPasswd = new QLineEdit;
    lineEditDBName = new QLineEdit;
    lineEditHostIP = new QLineEdit;

    loginBtn = new QPushButton(tr("登录"));
    logoutBtn = new QPushButton(tr("注销"));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(label0, 0, 0);
    layout->addWidget(lineEditUserID, 0, 1);
    layout->addWidget(label1, 1, 0);
    layout->addWidget(lineEditPasswd, 1, 1);
    layout->addWidget(label2, 2, 0);
    layout->addWidget(lineEditDBName, 2, 1);
    layout->addWidget(label3, 3, 0);
    layout->addWidget(lineEditHostIP, 3, 1);
    layout->addWidget(loginBtn, 4, 0);
    layout->addWidget(logoutBtn, 4, 1);

    layout->setColumnStretch(0, 1);//两列，设置两列大小相等
    layout->setColumnStretch(1, 1);

    layout->setMargin(15);//设置layout边距
    layout->setSpacing(10);//设置layout当中控件与控件的间距
    layout->setSizeConstraint(QLayout::SetFixedSize);//设置对话框大小不可改变

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/icon/2.jpg")));
    setPalette(palette);

    connect(loginBtn, SIGNAL(clicked()), this, SLOT(on_loginBtn()));
    connect(logoutBtn, SIGNAL(clicked()), this, SLOT(on_logoutBtn()));

}

void logindlg::on_logoutBtn()
{
        QMessageBox::information(this, " ", " ");
    close();
}

void logindlg::on_loginBtn()
{
    userid = lineEditUserID->text();
    passwd= lineEditPasswd->text();
    dbname = lineEditDBName->text();
    hostip = lineEditHostIP->text();
    islogin = true;
    close();
}
