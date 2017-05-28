#include "delete_celldlg.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>

delete_cellDlg::delete_cellDlg(QWidget *parent) :
    QDialog(parent)
{
    cellidlabel = new QLabel;
    cellidlabel->setText(tr("������Ҫɾ���Ļ�վ���"));
    cellid = new QLineEdit;

    okBtn = new QPushButton;
    okBtn->setText(tr("ɾ��"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("ȡ��"));

    QGridLayout *layout1 = new QGridLayout(this);

    layout1->addWidget(cellidlabel, 0, 0);
    layout1->addWidget(cellid, 0, 1);

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
    setWindowTitle(tr("ɾ����վ"));
    cellid->setFocus();
}

#define DELETECELL "delete from cells where cellid = %1"


void delete_cellDlg::okBtnOnclick()
{
    if (cellid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("����"), tr("��վ��Ų���Ϊ��"));
        cellid->setFocus();
        return ;
    }

    isok = true;
    SQL = QString(DELETECELL).arg(cellid->text());
    close();

}

void delete_cellDlg::cancelBtnOnclick()
{
    close();
}
