#include "logindlg.h"

#include <QGridLayout>
#include <QPalette>
#include <QMessageBox>

logindlg::logindlg()
{
    setWindowTitle(tr("��¼"));
    islogin = false;
    label0 = new QLabel(tr("�û���"));
    label1 = new QLabel(tr("����"));
    label2 = new QLabel(tr("���ݿ�����"));
    label3 = new QLabel(tr("������IP"));

    lineEditUserID = new QLineEdit;
    lineEditPasswd = new QLineEdit;
    lineEditDBName = new QLineEdit;
    lineEditHostIP = new QLineEdit;

    loginBtn = new QPushButton(tr("��¼"));
    logoutBtn = new QPushButton(tr("ע��"));

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

    layout->setColumnStretch(0, 1);//���У��������д�С���
    layout->setColumnStretch(1, 1);

    layout->setMargin(15);//����layout�߾�
    layout->setSpacing(10);//����layout���пؼ���ؼ��ļ��
    layout->setSizeConstraint(QLayout::SetFixedSize);//���öԻ����С���ɸı�

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
