#ifndef INSERT_BSCDLG_H
#define INSERT_BSCDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

class insert_bscDlg : public QDialog
{
    Q_OBJECT
public:
    explicit insert_bscDlg(QWidget *parent = 0);

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

#endif // INSERT_BSCDLG_H
