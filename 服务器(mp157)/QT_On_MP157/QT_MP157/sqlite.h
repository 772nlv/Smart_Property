#ifndef SQLITE_H
#define SQLITE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
class Sqlite
{
public:
    //构造函数
    Sqlite();
    //打开数据库
    void open_db();
    //创建数据表
    void creat_table();
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    //增加、删除、修改通用数据库函数
    void normalFunc(QString Sql);
    //查询 数据库函数
    void normalSearch(QString Sql,QSqlQuery &query);
private:
    //数据库
    QSqlDatabase database;
};

#endif // SQLITE_H
