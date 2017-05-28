#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>
#include "select_bscdlg.h"

select_bscDlg::select_bscDlg(QWidget *parent) :
    QDialog(parent)
{
    bscidlabel = new QLabel;
    bscidlabel->setText(tr("请输入基站控制器ID"));
    bscid = new QLineEdit;

    okBtn = new QPushButton;
    okBtn->setText(tr("查询"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("取消"));

    QGridLayout *layout1 = new QGridLayout(this);
    layout1->addWidget(bscidlabel, 0, 0);
    layout1->addWidget(bscid, 0, 1);

    QHBoxLayout *layout2 = new QHBoxLayout();


    layout2->addWidget(okBtn);
    layout2->addWidget(cancelBtn);
    layout1->addLayout(layout2, 1, 1);


    layout1->setColumnStretch(0, 1);
    layout1->setColumnStretch(1, 3);

    layout1->setMargin(15);
    layout1->setSpacing(10);

    connect(okBtn,SIGNAL(clicked()), this, SLOT(okBtnOnclick()));
    connect(cancelBtn,SIGNAL(clicked()), this, SLOT(cancelBtnOnclick()));

    isok = false;
    setWindowIcon(QIcon("main.png"));
    setWindowTitle(tr("查询基站控制器"));
    bscid->setFocus();
}

#define SELECTBSC1 "select a.bscid, a.bscpc StationControlCode, a.bscname StationControlName, a.branchname substation, DATE_FORMAT(a.createdate, '%Y-%m-%d') time, b.mscpc MSDCode, b.mscname MSCName, b.districtname domainName, a.description desc from bscs a, mscs b where a.mscid = b.mscid"
#define SELECTBSC2 "select a.bscid, a.bscpc StationControlCode, a.bscname StationControlName, a.branchname substation, DATE_FORMAT(a.createdate, '%Y-%m-%d') time, b.mscpc MSDCode, b.mscname MSCName, b.districtname domainName, a.description desc from bscs a, mscs b where a.mscid = b.mscid and a.bscid = %1"


void select_bscDlg::okBtnOnclick()
{
    isok = true;

    if (bscid->text().trimmed().isEmpty())
    {
        SQL = SELECTBSC1;
    }else
    {
        SQL = QString(SELECTBSC2).arg(bscid->text());
    }
    close();
}

void select_bscDlg::cancelBtnOnclick()
{
    close();
}


