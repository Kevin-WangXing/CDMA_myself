#ifndef SELECT_BSCDLG_H
#define SELECT_BSCDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

class select_bscDlg : public QDialog
{
    Q_OBJECT
public:
    explicit select_bscDlg(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *bscidlabel;
    QLineEdit *bscid;

    QPushButton *okBtn;
    QPushButton *cancelBtn;

private slots:
    void okBtnOnclick();
    void cancelBtnOnclick();

public:
    QString SQL;
    bool isok;

};

#endif // SELECT_BSCDLG_H
