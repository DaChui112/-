#ifndef SQLITEDRIVER_H
#define SQLITEDRIVER_H
#include <QString>
#include <QtSql>
#include <QDate>

#include "../Configer/confighelper.hpp"

#define SQL_PATH "./"

class sqliteDriver:public QObject
{
   Q_OBJECT
public:
    sqliteDriver();
    int creatSqlFile(QString _sqlname);
    int openSqliteFile(QString _sqlname);
    int createTable(const QString& tableName,const QStringList& HeaderList);
    int delTable(const QString& tableName);
    int addData(QString tableName,QHash<QString,QString> data);
    int delData(QString tableName,QString sqlWhere);
    int updateData(QString tableName,QHash<QString,QString> data,QString sqlWhere);
    int getData(QString tableName,QList<QHash<QString,QString>> &data,QString sqlWhere);
    int getCount(QString tableName,int &count,QString sqlWhere);
    int addCol(QString tableName, QString colName, QString colAfter);
    int getTableHeaders(QString tableName, QStringList &slHeaders);
private:
    QString ad_path;
};

#endif // SQLITEDRIVER_H
