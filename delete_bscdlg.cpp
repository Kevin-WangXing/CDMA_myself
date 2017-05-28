#include "delete_bscdlg.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>

delete_bscDlg::delete_bscDlg(QWidget *parent) :
    QDialog(parent)
{
    bscidlabel = new QLabel;
    bscidlabel->setText(tr("ÇëÊäÈëÒªÉ¾³ýµÄ»ùÕ¾¿ØÖÆÆ÷±àºÅ"));
    bscid = new QLineEdit;

    okBtn = new QPushButton;
    okBtn->setText(tr("É¾³ý"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("È¡Ïû"));

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
    setWindowTitle(tr("É¾³ý»ùÕ¾¿ØÖÆÆ÷"));
    bscid->setFocus();
}

#define DELETEBSC "delete from bscs where bscid = %1"

void delete_bscDlg::okBtnOnclick()
{
    if (bscid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("´íÎó"), tr("»ùÕ¾¿ØÖÆÆ÷±àºÅ²»ÄÜÎª¿Õ"));
        bscid->setFocus();
        return ;
    }

    isok = true;
    SQL = QString(DELETEBSC).arg(bscid->text());
    close();
}

void delete_bscDlg::cancelBtnOnclick()
{
    close();
}
