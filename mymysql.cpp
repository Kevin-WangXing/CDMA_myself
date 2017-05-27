#include "mymysql.h"

#include <QMessageBox>
#include <Qstring>

mymysql::mymysql()
{
    mysql_init(&mysql);
    connection = NULL;
    memset(buf, 0, sizeof(buf));
}

const char * mymysql::geterror()
{
    return buf;
}

int mymysql::sql_connect(const char *Hostname, const char *User, const char *Passwd, const char *DBName)
{
    connection = mysql_real_connect(&mysql, Hostname, User, Passwd, DBName, 0, 0, 0);
    if(connection == NULL)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        QMessageBox::information(0, "1", mysql_error(&mysql));
        return -1;
    }else
    {
        mysql_query(connection, "set names utf8");
        return 0;
    }
}

void mymysql::sql_disconnect()
{
    if(connection)
    {
        mysql_close(connection);
        connection = NULL;
    }
}

int mymysql::sql_exec(const char *SQL)
{
    if(mysql_query(connection, SQL) != 0)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }
    return 0;
}

int mymysql::sql_open(const char *SQL, QStandardItemModel **p)
{
    if(mysql_query(connection, SQL) != 0)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(result == NULL)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }

    int rowcount = mysql_affected_rows(connection);//行
    int filedcount = mysql_field_count(connection);//列

    //根据SQL语句返回的行列数，动态的建立一个module出来
    *p = new QStandardItemModel(rowcount, filedcount);

    MYSQL_FIELD *field;

    int i = 0;
    int j = 0;
    for(i = 0; i < filedcount; i++)
    {
        field = mysql_fetch_field(result);
        (*p)->setHeaderData(i, Qt::Horizontal, field->name);
    }

    for(i = 0; i < rowcount; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        for(j = 0; j < filedcount; j++)
        {
            (*p)->setData((*p)->index(i, j, QModelIndex()), row[j]);
        }
    }

    mysql_free_result(result);
    return 0;
}
