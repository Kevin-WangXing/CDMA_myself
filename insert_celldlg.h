#ifndef INSERT_CELLDLG_H
#define INSERT_CELLDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

class insert_cellDlg : public QDialog
{
    Q_OBJECT
public:
    explicit insert_cellDlg(QWidget *parent = 0);

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

#endif // INSERT_CELLDLG_H
