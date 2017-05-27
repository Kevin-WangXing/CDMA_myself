#ifndef MYMYSQL_H
#define MYMYSQL_H

#include <Windows.h>
#include <C:/mymysql/mysql/include/mysql.h>
#include <QStandardItemModel>

class mymysql
{
public:
    mymysql();
    const char *geterror();
    int sql_connect(const char *Hostname, const char *User, const char * Passwd, const char *DBName);
    void sql_disconnect();
    int sql_exec(const char *SQL);
    int sql_open(const char *SQL, QStandardItemModel **p);

private:
    MYSQL *connection;
    MYSQL mysql;
    char buf[1024];

};

#endif // MYMYSQL_H
