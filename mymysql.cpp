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
//执行SELECT语句，将查询结果放入QStringList当中
int mymysql::sql_open_str(const char *SQL, QStringList &list)
{
    int state = mysql_query(connection, SQL);//执行SQL语句
    if (state != 0)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;//执行失败，返回-1
    }

    MYSQL_RES *result = mysql_store_result(connection);//得到查询结果
    if (result == (MYSQL_RES *) NULL)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;//执行失败，返回-1
    } else
    {
        MYSQL_ROW sqlRow;
        sqlRow = mysql_fetch_row(result);
        if (sqlRow == NULL)
            return -1;
        int icount = mysql_field_count(connection);
        int i;
        for (i = 0; i < icount; i++)//循环得到一行中的每个字段
        {
            if (sqlRow[i] == NULL)//如果值为NULL，向model中插入字符串"NULL"
            {
                list.append("NULL");//将行中的每一列的值放入list中
            }else
            {
                list.append((const char *)sqlRow[i]);//将行中的每一列的值放入list中
            }
        }
        //printf("query is ok, %u rows affected\n", (unsigned int)mysql_affected_rows(connection));
        mysql_free_result(result);
    }
    return 0;
}

