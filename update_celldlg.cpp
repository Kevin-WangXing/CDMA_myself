#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>
#include "update_celldlg.h"

update_cellDlg::update_cellDlg(QString &cellid1, QString &cellname1,
                               QString &bscid1, QString &createdate1, QString &longitude1,
                               QString &latitude1, QString &description1, QWidget *parent) :
    QDialog(parent)
{
    cellidlabel = new QLabel;
    cellidlabel->setText(tr("基站编号"));
    cellid = new QLineEdit;
    cellid->setText(cellid1);
    cellid->setEnabled(false);


    cellnamelabel = new QLabel;
    cellnamelabel->setText(tr("请输入基站名称"));
    cellname = new QLineEdit;
    cellname->setText(cellname1);

    bscidlabel = new QLabel;
    bscidlabel->setText(tr("请输入基站名称"));
    bscid = new QLineEdit;
    bscid->setText(bscid1);

    createdatelabel = new QLabel;
    createdatelabel->setText(tr("请选择基站建立日期"));
    createdate = new QDateEdit;
    createdate->setDisplayFormat("yyyy-M-d");

    QMessageBox::information(this, "create",createdate1);
    createdate->setDate(QDate::fromString(createdate1, "yyyy-M-d"));

    longitudelablel = new QLabel;
    longitudelablel->setText(tr("请输入基站经度"));
    longitude = new QLineEdit;
    longitude->setText(longitude1);

    latitudelabel = new QLabel;
    latitudelabel->setText(tr("请输入基站纬度"));
    latitude = new QLineEdit;
    latitude->setText(latitude1);

    descriptionlabel = new QLabel;
    descriptionlabel->setText(tr("请输入基站描述"));
    description = new QLineEdit;
    description->setText(description1);

    okBtn = new QPushButton;
    okBtn->setText(tr("修改"));
    cancelBtn = new QPushButton;
    cancelBtn->setText(tr("取消"));

    QGridLayout *layout1 = new QGridLayout(this);

    layout1->addWidget(cellidlabel, 0, 0);
    layout1->addWidget(cellid, 0, 1);

    layout1->addWidget(cellnamelabel, 1, 0);
    layout1->addWidget(cellname, 1, 1);

    layout1->addWidget(createdatelabel, 2, 0);
    layout1->addWidget(createdate, 2, 1);

    layout1->addWidget(bscidlabel, 3, 0);
    layout1->addWidget(bscid, 3, 1);

    layout1->addWidget(createdatelabel, 4, 0);
    layout1->addWidget(createdate, 4, 1);

    layout1->addWidget(longitudelablel, 5, 0);
    layout1->addWidget(longitude, 5, 1);

    layout1->addWidget(latitudelabel, 6, 0);
    layout1->addWidget(latitude, 6, 1);

    layout1->addWidget(descriptionlabel, 7, 0);
    layout1->addWidget(description, 7, 1);

    QHBoxLayout *layout2 = new QHBoxLayout();

    layout2->addWidget(okBtn);
    layout2->addWidget(cancelBtn);
    layout1->addLayout(layout2, 8, 1);

    layout1->setColumnStretch(0, 1);
    layout1->setColumnStretch(1, 3);

    layout1->setMargin(15);
    layout1->setSpacing(10);

    connect(okBtn,SIGNAL(clicked()), this, SLOT(okBtnOnclick()));
    connect(cancelBtn,SIGNAL(clicked()), this, SLOT(cancelBtnOnclick()));

    isok = false;
    setWindowIcon(QIcon("main.png"));
    setWindowTitle(tr("添加基站"));
    cellid->setFocus();
}


#define UPDATECELL "update cells set cellname = '%1', bscid = %2, createdate = str_to_date('%3','%Y-%m-%d %H:%i:%s'), longitude = '%4', latitude = '%5', description = '%6' where cellid = %7"
void update_cellDlg::okBtnOnclick()
{
    if (cellid->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("基站编号不能为空"));
        cellid->setFocus();
        return ;
    }

    if (cellname->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, tr("错误"), tr("基站名称不能为空"));
        cellname->setFocus();
        return ;
    }

    isok = true;
    SQL = QString(UPDATECELL).arg(cellname->text()).arg(bscid->text()).arg(createdate->text()).arg(longitude->text()).arg(latitude->text()).arg(description->text()).arg(cellid->text());
    close();

}

void update_cellDlg::cancelBtnOnclick()
{
    close();
}


