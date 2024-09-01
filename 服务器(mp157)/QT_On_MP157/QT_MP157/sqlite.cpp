#include "sqlite.h"

Sqlite::Sqlite()
{
    //程序使用的数据库文件是和应用文件一个目录的，可以设置为：

    //检查是否已存在名为"qt_sql_default_connection"的数据库连接。
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
        qDebug()<<"creat Sqlite success";
    }
    else
    {
        // 建立和SQlite数据库的连接,指定类型为Sqlite
        database = QSqlDatabase::addDatabase("QSQLITE");
        // 设置数据库文件的名字
        database.setDatabaseName("./stm32DataBase.db");
        qDebug()<<"creat Sqlite success";
    }
}

//open sqlite
void Sqlite::open_db()
{
    if (!database.open())
    {
       qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
       qDebug()<<"connect Sqlite success"<<database.databaseName();
       // do something
    }
}

//creat table
void Sqlite::creat_table()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE DATA(Temp TEXT,Humi TEXT,Light TEXT,Poten TEXT,Time TEXT)");
    if(!query.exec())
    {
        qDebug() << "Error: Fail to create table. " << query.lastError();
    }
    else
    {
        qDebug() << "table created!";
    }
}

bool Sqlite::isTableExist(QString &tableName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if(database.tables().contains(tableName))
    {
       return true;
    }
    return false;
}

//sql normol func
void Sqlite::normalFunc(QString Sql)
{
    QSqlQuery query;
    query.prepare(Sql);
    if(!query.exec())
    {
       qDebug() << "Error: Fail to work. " << query.lastError();

    }
    else
    {
       qDebug() << "succese!";
    }
}

void Sqlite::normalSearch(QString Sql, QSqlQuery &query)
{
    query.prepare(Sql);
    if(!query.exec())
    {
        qDebug() << "Error: Fail to work. " << query.lastError();

    }
    else
    {
       qDebug() << "succese!";
    }
}

