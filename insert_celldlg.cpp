#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDate>
#include "insert_celldlg.h"

insert_cellDlg::insert_cellDlg(QWidget *parent) :
    QDialog(parent)
{
    cellidlabel = new QLabel;
    cellidlabel->setText(tr("请输入基站编号"));
    cellid = new QLineEdit;

    cellnamelabel = new QLabel;
    cellnamelabel->setText(tr("请输入基站名称"));
    cellname = new QLineEdit;

    bscidlabel = new QLabel;
    bscidlabel->setText(tr("请输入基站名称"));
    bscid = new QLineEdit;

    createdatelabel = new QLabel;
    createdatelabel->setText(tr("请选择基站建立日期"));
    createdate = new QDateEdit;
    createdate->setDisplayFormat("yyyy-M-d");
    createdate->setDate(QDate::currentDate());

    longitudelablel = new QLabel;
    longitudelablel->setText(tr("请输入基站经度"));
    longitude = new QLineEdit;

    latitudelabel = new QLabel;
    latitudelabel->setText(tr("请输入基站纬度"));
    latitude = new QLineEdit;

    descriptionlabel = new QLabel;
    descriptionlabel->setText(tr("请输入基站描述"));
    description = new QLineEdit;

    okBtn = new QPushButton;
    okBtn->setText(tr("添加"));
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

//#define INSERTCELL "<SQL>INSERT INTO cells (cellid, name, createdate, description) VALUES (%1, '%2', str_to_date('%3','%Y-%m-%d %H:%i:%s'), '%4')"

#define INSERTCELL "insert into cells (cellid, cellname, bscid, createdate, longitude, latitude, description) values (%1, '%2', %3, str_to_date('%4','%Y-%m-%d %H:%i:%s'),'%5', '%6', '%7')"


void insert_cellDlg::okBtnOnclick()
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
    SQL = QString(INSERTCELL).arg(cellid->text()).arg(cellname->text()).arg(bscid->text()).arg(createdate->text()).arg(longitude->text()).arg(latitude->text()).arg(description->text());
    close();

}

void insert_cellDlg::cancelBtnOnclick()
{
    close();
}


