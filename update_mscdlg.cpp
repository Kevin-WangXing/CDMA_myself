#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>
#include "update_mscdlg.h"

update_mscDlg::update_mscDlg(QString &mscid1, QString &mscpc1, QString &mscname1,
                               QString &districtname1, QString &createdate1, QString &description1, QWidget *parent) :
    QDialog(parent)
{
    mscidlabel = new QLabel;
    mscidlabel->setText(tr("MSCID"));
    mscid = new QLineEdit;
    mscid->setText(mscid1);
    mscid->setEnabled(false);

    mscpclabel = new QLabel;
    mscpclabel->setText(tr("请输入MSC点码"));
    mscpc = new QLineEdit;
    mscpc->setText(mscpc1);

    mscnamelabel = new QLabel;
    mscnamelabel->setText(tr("请输入MSC名称"));
    mscname = new QLineEdit;
    mscname->setText(mscname1);

    districtnamelabel = new QLabel;
    districtnamelabel->setText(tr("请输入所属区域名称"));
    districtname = new QLineEdit;
    districtname->setText(districtname1);

    createdatelabel = new QLabel;
    createdatelabel->setText(tr("请选择MSC建立日期"));
    createdate = new QDateEdit;
    createdate->setDisplayFormat("yyyy-M-d");
    createdate->setDate(QDate::fromString(createdate1, "yyyy-M-d"));

    descriptionlabel = new QLabel;
    descriptionlabel->setText(tr("请输入MSC描述"));
    description = new QLineEdit;
    description->setText(description1);

    okBtn = new QPushButton;
    okBtn->setText(tr("修改"));
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
    setWindowTitle(tr("修改MSC"));
    mscid->setFocus();
}


#define UPDATEMSC "update mscs set mscpc = '%1', mscname = '%2', districtname = '%3', createdate = str_to_date('%4','%Y-%m-%d %H:%i:%s'), description = '%5' where mscid = %6"
void update_mscDlg::okBtnOnclick()
{
    if (mscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("基站编号不能为空"));
        mscid->setFocus();
        return ;
    }

    if (mscname->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("基站名称不能为空"));
        mscname->setFocus();
        return ;
    }

    isok = true;
    SQL = QString(UPDATEMSC).arg(mscpc->text()).arg(mscname->text()).arg(districtname->text()).arg(createdate->text()).arg(description->text()).arg(mscid->text());
    close();

}

void update_mscDlg::cancelBtnOnclick()
{
    close();
}


