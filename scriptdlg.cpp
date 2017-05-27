#include "scriptdlg.h"
#include <QHBoxLayout>
#include <QGridLayout>

scriptDlg::scriptDlg(QWidget *parent) :
    QDialog(parent)
{
    islogin = false;
    label0 = new QLabel(tr("������SQL"));
    textEditSQL = new QTextEdit;

    okBtn = new QPushButton(tr("ִ��"));
    cancelBtn = new QPushButton(tr("ȡ��"));

    QGridLayout *layout1 = new QGridLayout(this);
    layout1->addWidget(label0, 0, 0);
    layout1->addWidget(textEditSQL, 0, 1);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(okBtn);
    layout2->addWidget(cancelBtn);
    layout1->addLayout(layout2, 1, 1);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(on_okBtn()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(on_cancelBtn()));
}

void scriptDlg::on_okBtn()
{
    SQL = textEditSQL->toPlainText();
    islogin = true;
    close();
}

void scriptDlg::on_cancelBtn()
{
    close();
}
