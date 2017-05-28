#ifndef UPDATE_CELLDLG_H
#define UPDATE_CELLDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

class update_cellDlg : public QDialog
{
    Q_OBJECT
public:
    explicit update_cellDlg(QString &cellid1, QString &cellname1,
                            QString &bscid1, QString &createdate1, QString &longitude1,
                            QString &latitude1, QString &description1, QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *cellidlabel, *cellnamelabel, *bscidlabel, *createdatelabel,
        *longitudelablel, *latitudelabel, *descriptionlabel;
    QLineEdit *cellid, *cellname, *bscid,
        *longitude, *latitude, *description;
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

#endif // UPDATE_CELLDLG_H
