#ifndef UPDATE_MSCDLG_H
#define UPDATE_MSCDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>


class update_mscDlg : public QDialog
{
    Q_OBJECT
public:
    explicit update_mscDlg(QString &mscid1, QString &mscpc1, QString &mscname1,
                           QString &districtname1, QString &createdate1, QString &description1, QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *mscidlabel, *mscpclabel, *mscnamelabel,
        *districtnamelabel, *createdatelabel, *descriptionlabel;
    QLineEdit *mscid, *mscpc, *mscname,
        *districtname, *description;
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

#endif // UPDATE_MSCDLG_H
