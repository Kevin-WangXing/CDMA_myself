#ifndef SCRIPTDLG_H
#define SCRIPTDLG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

class scriptDlg : public QDialog
{
    Q_OBJECT
public:
    explicit scriptDlg(QWidget *parent = 0);

    bool islogin;
    QString SQL;

private:
    QLabel *label0;
    QTextEdit *textEditSQL;
    QPushButton *okBtn;
    QPushButton *cancelBtn;


signals:

private slots:
    void on_okBtn();
    void on_cancelBtn();
public slots:

};

#endif // SCRIPTDLG_H
