#ifndef SELECT_CELLDLG_H
#define SELECT_CELLDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

class select_cellDlg : public QDialog
{
    Q_OBJECT
public:
    explicit select_cellDlg(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *cellidlabel;
    QLineEdit *cellid;

    QPushButton *okBtn;
    QPushButton *cancelBtn;

private slots:
    void okBtnOnclick();
    void cancelBtnOnclick();

public:
    QString SQL;
    bool isok;

};

#endif // SELECT_CELLDLG_H
