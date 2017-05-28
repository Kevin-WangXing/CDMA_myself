#ifndef DELETE_BSCDLG_H
#define DELETE_BSCDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

class delete_bscDlg : public QDialog
{
    Q_OBJECT
public:
    explicit delete_bscDlg(QWidget *parent = 0);

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

#endif // DELETE_BSCDLG_H
