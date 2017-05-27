#include "insert_mscdlg.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>

insert_mscDlg::insert_mscDlg(QWidget *parent) :
    QDialog(parent)
{
    mscidlabel = new QLabel;
    mscidlabel->setText(tr("������MSCID"));
    mscid = new QLineEdit;

    mscpclabel = new QLabel;
    mscpclabel->setText(tr("������MSC����"));
    mscpc = new QLineEdit;

    mscnamelabel = new QLabel;
    mscnamelabel->setText(tr("������MSC����"));
    mscname = new QLineEdit;

    districtnamelabel = new QLabel;
    districtnamelabel->setText(tr("������������������"));
    districtname = new QLineEdit;

    createdatelabel = new QLabel;
    createdatelabel->setText(tr("��ѡ��MSC��������"));
    createdate = new QDateEdit;
    createdate->setDisplayFormat("yyyy-M-d");
    createdate->setDate(QDate::currentDate());

    descriptionlabel = new QLabel;
    descriptionlabel->setText(tr("������MSC����"));
    description = new QLineEdit;

    okBtn = new QPushButton;
    okBtn->setText(tr("���"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("ȡ��"));

    QGridLayout *layout1 = new QGridLayout(this);

    layout1->addWidget(mscidlabel, 0, 0);
    layout1->addWidget(mscid, 0, 1);

    layout1->addWidget(mscpclabel, 1, 0);
    layout1->addWidget(mscpc, 1, 1);

    layout1->addWidget(mscnamelabel, 2, 0);
    layout1->addWidget(mscname, 2, 1);

    layout1->addWidget(districtnamelabel, 3, 0);
    layout1->addWidget(districtname, 3, 1);

    layout1->addWidget(createdatelabel, 4, 0);
    layout1->addWidget(createdate, 4, 1);

    layout1->addWidget(descriptionlabel, 5, 0);
    layout1->addWidget(description, 5, 1);

    QHBoxLayout *layout2 = new QHBoxLayout();

    layout2->addWidget(okBtn);
    layout2->addWidget(cancelBtn);
    layout1->addLayout(layout2, 6, 1);

    layout1->setColumnStretch(0, 1);
    layout1->setColumnStretch(1, 3);

    layout1->setMargin(15);
    layout1->setSpacing(10);

    connect(okBtn,SIGNAL(clicked()), this, SLOT(okBtnOnclick()));
    connect(cancelBtn,SIGNAL(clicked()), this, SLOT(cancelBtnOnclick()));

    isok = false;
    setWindowIcon(QIcon("main.png"));
    setWindowTitle(tr("���MSC"));
    mscid->setFocus();
}

#define INSERTMSC "insert into mscs (mscid, mscpc, mscname, districtname, createdate, description) values (%1, '%2', '%3', '%4', str_to_date('%5','%Y-%m-%d %H:%i:%s'), '%6')"

void insert_mscDlg::okBtnOnclick()
{
    if (mscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("����"), tr("��վ��������Ų���Ϊ��"));
        mscid->setFocus();
        return ;
    }

    if (mscname->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("����"), tr("��վ���������Ʋ���Ϊ��"));
        mscname->setFocus();
        return ;
    }

    if (mscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("����"), tr("MSCID����Ϊ��"));
        mscid->setFocus();
        return ;
    }

    isok = true;

    SQL = QString(INSERTMSC).arg(mscid->text()).arg(mscpc->text()).arg(mscname->text()).arg(districtname->text()).arg(createdate->text()).arg(description->text());
    close();

}

void insert_mscDlg::cancelBtnOnclick()
{
    close();
}
