#include "delete_mscdlg.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>

delete_mscDlg::delete_mscDlg(QWidget *parent) :
    QDialog(parent)
{
    mscidlabel = new QLabel;
    mscidlabel->setText(tr("������Ҫɾ����MSCID"));
    mscid = new QLineEdit;

    okBtn = new QPushButton;
    okBtn->setText(tr("ɾ��"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("ȡ��"));

    QGridLayout *layout1 = new QGridLayout(this);

    layout1->addWidget(mscidlabel, 0, 0);
    layout1->addWidget(mscid, 0, 1);

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
    setWindowTitle(tr("ɾ��MSC"));
    mscid->setFocus();
}

#define DELETEMSC "delete from mscs where mscid = %1"

void delete_mscDlg::okBtnOnclick()
{
    if (mscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("����"), tr("MSCID����Ϊ��"));
        mscid->setFocus();
        return ;
    }

    isok = true;
    SQL = QString(DELETEMSC).arg(mscid->text());
    close();

}

void delete_mscDlg::cancelBtnOnclick()
{
    close();
}
