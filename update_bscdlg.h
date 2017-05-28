#ifndef UPDATE_BSCDLG_H
#define UPDATE_BSCDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>


class update_bscDlg : public QDialog
{
Q_OBJECT
public:
    explicit update_bscDlg(QString &bscid1, QString &bscpc1, QString &bscname1,
                           QString &mscid1, QString &branchname1, QString &createdate1,
                                  QString &description1, QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *bscidlabel, *bscpclabel, *bscnamelabel,
        *mscidlabel, *branchnamelabel, *createdatelabel, *descriptionlabel;
    QLineEdit *bscid, *bscpc, *bscname,
        *mscid, *branchname, *description;
    QDateEdit *createdate;

    QPushButton *okBtn;
    QPushButton *cancelBtn;

private slots:
    void okBtnOnclick();
    void cancelBtnOnclick();

public:
    QString SQL;
    bool isok;

};

#endif // UPDATE_BSCDLG_H
