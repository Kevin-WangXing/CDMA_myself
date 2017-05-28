#include "insert_bscdlg.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>

insert_bscDlg::insert_bscDlg(QWidget *parent) :
    QDialog(parent)
{
    bscidlabel = new QLabel;
    bscidlabel->setText(tr("请输入基站控制器编号"));
    bscid = new QLineEdit;

    bscpclabel = new QLabel;
    bscpclabel->setText(tr("请输入基站控制器点码"));
    bscpc = new QLineEdit;

    bscnamelabel = new QLabel;
    bscnamelabel->setText(tr("请输入基站控制器名称"));
    bscname = new QLineEdit;

    mscidlabel = new QLabel;
    mscidlabel->setText(tr("请输入所属MSCID"));
    mscid = new QLineEdit;

    branchnamelabel = new QLabel;
    branchnamelabel->setText(tr("请输入所属支局名称"));
    branchname = new QLineEdit;

    createdatelabel = new QLabel;
    createdatelabel->setText(tr("请选择基站控制器建立日期"));
    createdate = new QDateEdit;
    createdate->setDisplayFormat("yyyy-M-d");
    createdate->setDate(QDate::currentDate());

    descriptionlabel = new QLabel;
    descriptionlabel->setText(tr("请输入基站控制器描述"));
    description = new QLineEdit;

    okBtn = new QPushButton;
    okBtn->setText(tr("添加"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("取消"));

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
    setWindowTitle(tr("添加基站控制器"));
    bscid->setFocus();
}

#define INSERTBSC "insert into bscs (bscid, bscpc, bscname, mscid, branchname, createdate, description) values (%1, '%2', '%3', %4, '%5', str_to_date('%6','%Y-%m-%d %H:%i:%s'),'%7')"

void insert_bscDlg::okBtnOnclick()
{
    if (bscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("基站控制器编号不能为空"));
        bscid->setFocus();
        return ;
    }

    if (bscname->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("基站控制器名称不能为空"));
        bscname->setFocus();
        return ;
    }

    if (mscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("MSCID不能为空"));
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

