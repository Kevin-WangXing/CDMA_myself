#include "insert_bscdlg.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>

insert_bscDlg::insert_bscDlg(QWidget *parent) :
    QDialog(parent)
{
    bscidlabel = new QLabel;
    bscidlabel->setText(tr("�������վ���������"));
    bscid = new QLineEdit;

    bscpclabel = new QLabel;
    bscpclabel->setText(tr("�������վ����������"));
    bscpc = new QLineEdit;

    bscnamelabel = new QLabel;
    bscnamelabel->setText(tr("�������վ����������"));
    bscname = new QLineEdit;

    mscidlabel = new QLabel;
    mscidlabel->setText(tr("����������MSCID"));
    mscid = new QLineEdit;

    branchnamelabel = new QLabel;
    branchnamelabel->setText(tr("����������֧������"));
    branchname = new QLineEdit;

    createdatelabel = new QLabel;
    createdatelabel->setText(tr("��ѡ���վ��������������"));
    createdate = new QDateEdit;
    createdate->setDisplayFormat("yyyy-M-d");
    createdate->setDate(QDate::currentDate());

    descriptionlabel = new QLabel;
    descriptionlabel->setText(tr("�������վ����������"));
    description = new QLineEdit;

    okBtn = new QPushButton;
    okBtn->setText(tr("���"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("ȡ��"));

    QGridLayout *layout1 = new QGridLayout(this);

    layout1->addWidget(bscidlabel, 0, 0);
    layout1->addWidget(bscid, 0, 1);

    layout1->addWidget(bscpclabel, 1, 0);
    layout1->addWidget(bscpc, 1, 1);

    layout1->addWidget(bscnamelabel, 2, 0);
    layout1->addWidget(bscname, 2, 1);

    layout1->addWidget(mscidlabel, 3, 0);
    layout1->addWidget(mscid, 3, 1);

    layout1->addWidget(branchnamelabel, 4, 0);
    layout1->addWidget(branchname, 4, 1);

    layout1->addWidget(createdatelabel, 5, 0);
    layout1->addWidget(createdate, 5, 1);

    layout1->addWidget(descriptionlabel, 6, 0);
    layout1->addWidget(description, 6, 1);

    QHBoxLayout *layout2 = new QHBoxLayout();

    layout2->addWidget(okBtn);
    layout2->addWidget(cancelBtn);
    layout1->addLayout(layout2, 7, 1);

    layout1->setColumnStretch(0, 1);
    layout1->setColumnStretch(1, 3);

    layout1->setMargin(15);
    layout1->setSpacing(10);

    connect(okBtn,SIGNAL(clicked()), this, SLOT(okBtnOnclick()));
    connect(cancelBtn,SIGNAL(clicked()), this, SLOT(cancelBtnOnclick()));

    isok = false;
    setWindowIcon(QIcon("main.png"));
    setWindowTitle(tr("��ӻ�վ������"));
    bscid->setFocus();
}

#define INSERTBSC "insert into bscs (bscid, bscpc, bscname, mscid, branchname, createdate, description) values (%1, '%2', '%3', %4, '%5', str_to_date('%6','%Y-%m-%d %H:%i:%s'),'%7')"

void insert_bscDlg::okBtnOnclick()
{
    if (bscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("����"), tr("��վ��������Ų���Ϊ��"));
        bscid->setFocus();
        return ;
    }

    if (bscname->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("����"), tr("��վ���������Ʋ���Ϊ��"));
        bscname->setFocus();
        return ;
    }

    if (mscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("����"), tr("MSCID����Ϊ��"));
        mscid->setFocus();
        return ;
    }

    isok = true;

    SQL = QString(INSERTBSC).arg(bscid->text()).arg(bscpc->text()).arg(bscname->text()).arg(mscid->text()).arg(branchname->text()).arg(createdate->text()).arg(description->text());
    close();

}

void insert_bscDlg::cancelBtnOnclick()
{
    close();
}

