#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

class logindlg : public QDialog
{
    Q_OBJECT
public:
    logindlg();

public:
    QString userid;
    QString passwd;
    QString dbname;
    QString hostip;
    bool islogin;

private:
    QLabel *label0, *label1, *label2, *label3;
    QLineEdit *lineEditUserID, *lineEditPasswd, *lineEditDBName, *lineEditHostIP;
    QPushButton *loginBtn, *logoutBtn;

private slots:
    void on_loginBtn();
    void on_logoutBtn();
};

#endif // LOGINDLG_H
