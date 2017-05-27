#include "select_mscdlg.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>

select_mscDlg::select_mscDlg(QWidget *parent) :
    QDialog(parent)
{
    mscidlabel = new QLabel(tr("请输入MSCID"));
    mscid = new QLineEdit;

    okBtn = new QPushButton(tr("查询"));
    cancelBtn = new QPushButton(tr("取消"));

    QGridLayout *layout1 = new QGridLayout(this);
    layout1->addWidget(mscidlabel, 0, 0);
    layout1->addWidget(mscid, 0, 1);

    QHBoxLayout *layout2 = new QHBoxLayout;

    layout2->addWidget(okBtn);
    layout2->addWidget(cancelBtn);
    layout1->addLayout(layout2, 1, 1);

    layout1->setColumnStretch(0, 1);
    layout1->setColumnStretch(1, 3);

    layout1->setMargin(15);
    layout1->setSpacing(10);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(okBtn_click()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(cancelBtn_click()));

    isok = false;
    //setWindowIcon(QIcon(":/icon/main.png"));
    setWindowTitle(tr("查询MSC"));
    mscid->setFocus();
}

void select_mscDlg::cancelBtn_click()
{
    close();
}

#define SELECTMSC1 "select mscid, mscpc MSCCode, mscname MSCName, districtname AreaName, DATE_FORMAT(createdate, '%Y-%m-%d') CreateTime, description Description from mscs"
#define SELECTMSC2 "select mscid, mscpc MSCCode, mscname MSCName, districtname AreaName, DATE_FORMAT(createdate, '%Y-%m-%d') CreateTime, description Description from mscs where mscid = %1"

void select_mscDlg::okBtn_click()
{
    isok = true;
    if(mscid->text().trimmed().isEmpty())
    {
        SQL = SELECTMSC1;
    }else
    {
        SQL = QString(SELECTMSC2).arg(mscid->text());
    }
    close();
}
