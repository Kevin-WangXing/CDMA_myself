#ifndef DELETE_CELLDLG_H
#define DELETE_CELLDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

class delete_cellDlg : public QDialog
{
    Q_OBJECT
public:
    explicit delete_cellDlg(QWidget *parent = 0);

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

#endif // DELETE_CELLDLG_H
