#ifndef INSERT_MSCDLG_H
#define INSERT_MSCDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

class insert_mscDlg : public QDialog
{
    Q_OBJECT
public:
    explicit insert_mscDlg(QWidget *parent = 0);

signals:

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

#endif // INSERT_MSCDLG_H
