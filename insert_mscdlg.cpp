#include "insert_mscdlg.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>

insert_mscDlg::insert_mscDlg(QWidget *parent) :
    QDialog(parent)
{
    mscidlabel = new QLabel;
    mscidlabel->setText(tr("请输入MSCID"));
    mscid = new QLineEdit;

    mscpclabel = new QLabel;
    mscpclabel->setText(tr("请输入MSC点码"));
    mscpc = new QLineEdit;

    mscnamelabel = new QLabel;
    mscnamelabel->setText(tr("请输入MSC名称"));
    mscname = new QLineEdit;

    districtnamelabel = new QLabel;
    districtnamelabel->setText(tr("请输入所属区域名称"));
    districtname = new QLineEdit;

    createdatelabel = new QLabel;
    createdatelabel->setText(tr("请选择MSC建立日期"));
    createdate = new QDateEdit;
    createdate->setDisplayFormat("yyyy-M-d");
    createdate->setDate(QDate::currentDate());

    descriptionlabel = new QLabel;
    descriptionlabel->setText(tr("请输入MSC描述"));
    description = new QLineEdit;

    okBtn = new QPushButton;
    okBtn->setText(tr("添加"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("取消"));

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
    setWindowTitle(tr("添加MSC"));
    mscid->setFocus();
}

#define INSERTMSC "insert into mscs (mscid, mscpc, mscname, districtname, createdate, description) values (%1, '%2', '%3', '%4', str_to_date('%5','%Y-%m-%d %H:%i:%s'), '%6')"

void insert_mscDlg::okBtnOnclick()
{
    if (mscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("基站控制器编号不能为空"));
        mscid->setFocus();
        return ;
    }

    if (mscname->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("基站控制器名称不能为空"));
        mscname->setFocus();
        return ;
    }

    if (mscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("MSCID不能为空"));
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
