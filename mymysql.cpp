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

    int rowcount = mysql_affected_rows(connection);//��
    int filedcount = mysql_field_count(connection);//��

    //����SQL��䷵�ص�����������̬�Ľ���һ��module����
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
//ִ��SELECT��䣬����ѯ�������QStringList����
int mymysql::sql_open_str(const char *SQL, QStringList &list)
{
    int state = mysql_query(connection, SQL);//ִ��SQL���
    if (state != 0)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;//ִ��ʧ�ܣ�����-1
    }

    MYSQL_RES *result = mysql_store_result(connection);//�õ���ѯ���
    if (result == (MYSQL_RES *) NULL)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;//ִ��ʧ�ܣ�����-1
    } else
    {
        MYSQL_ROW sqlRow;
        sqlRow = mysql_fetch_row(result);
        if (sqlRow == NULL)
            return -1;
        int icount = mysql_field_count(connection);
        int i;
        for (i = 0; i < icount; i++)//ѭ���õ�һ���е�ÿ���ֶ�
        {
            if (sqlRow[i] == NULL)//���ֵΪNULL����model�в����ַ���"NULL"
            {
                list.append("NULL");//�����е�ÿһ�е�ֵ����list��
            }else
            {
                list.append((const char *)sqlRow[i]);//�����е�ÿһ�е�ֵ����list��
            }
        }
        //printf("query is ok, %u rows affected\n", (unsigned int)mysql_affected_rows(connection));
        mysql_free_result(result);
    }
    return 0;
}

