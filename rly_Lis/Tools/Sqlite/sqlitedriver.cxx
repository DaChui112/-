#include "Tools\Sqlite\sqlitedriver.hpp"

sqliteDriver::sqliteDriver()
{
    ad_path=SQL_PATH;
    QString config_path=configHelper::readInit("Path","AD_Path");
    if(!config_path.isEmpty())
        ad_path=config_path;
}

int sqliteDriver::creatSqlFile(QString _sqlname)
{

    QDir temp;
    QString sqlName=ad_path;
    if(!temp.exists(sqlName))
        temp.mkdir(sqlName);
    sqlName+=_sqlname+".db";
    QSqlDatabase dbconn;
    if(!dbconn.contains("sqlite"))
        dbconn.removeDatabase("sqlite");
    dbconn= QSqlDatabase::addDatabase("QSQLITE","sqlite");
    dbconn.setDatabaseName(sqlName);
    qDebug()<<"sqlite数据库路径:"+sqlName;
    if(!dbconn.open())
    {
        if(!temp.exists(sqlName))
            qWarning()<<"文件未找到:"+dbconn.lastError().text();
        else
            qCritical()<<"sqlite数据库打开失败:"+dbconn.lastError().text();
        return -1;
    }

    return 0;
}

//开启数据库
int sqliteDriver::openSqliteFile(QString _sqlname)
{

    QDir temp;
    QString sqlName=ad_path;
    sqlName+=_sqlname+".db";
    if(!temp.exists(sqlName))
    {
        qDebug()<<"sqlite数据库文件不存在,新建数据库";
        return -1;
    }
    QSqlDatabase dbconn;
    if(!dbconn.contains("sqlite"))
        dbconn.removeDatabase("sqlite");
    dbconn= QSqlDatabase::addDatabase("QSQLITE","sqlite");
    dbconn.setDatabaseName(sqlName);

    qDebug()<<"sqlite数据库路径:"+sqlName;
    if(!dbconn.open())
    {
        if(!temp.exists(sqlName))
            qWarning()<<"文件未找到:"+dbconn.lastError().text();
        else
            qCritical()<<"sqlite数据库打开失败:"+dbconn.lastError().text();

        return -1;
    }

    return 0;
}

int sqliteDriver::createTable(const QString &tableName, const QStringList &HeaderList)
{
    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStr="CREATE TABLE "+tableName+" (item_name TEXT NOT NULL," + " item_code TEXT NOT NULL,";
    for(int i = 2; i < HeaderList.size(); i++)
    {
        queryStr += ' ' + HeaderList.at(i) + " TEXT,";
    }
    qDebug() << "createTable: " << queryStr;
    queryStr = queryStr.mid(0, queryStr.size() - 1) + ')';
    if(!query.exec(queryStr))
    {
        qCritical()<<"sql语句添加数据失败:"+query.lastError().text();
        return -1;
    }
    return 0;
}

int sqliteDriver::delTable(const QString &tableName)
{
    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStr="drop table "+tableName;
    qDebug() << "delTable: " << queryStr;
    if(!query.exec(queryStr))
    {
        qCritical()<<"sql语句添加数据失败:"+query.lastError().text();
        return -1;
    }
    return 0;
}

//插入或者覆盖数据
int sqliteDriver::addData(QString tableName,QHash<QString,QString> data)
{

    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStr="insert into "+tableName+" ";
    QString fieldStr="(",valueStr="values(";
    QHash<QString,QString>::iterator it;
    for ( it = data.begin(); it != data.end(); ++it )
    {
        fieldStr+=it.key()+",";
        valueStr+="'"+it.value()+"',";
    }
    fieldStr=fieldStr.left(fieldStr.length()-1);
    valueStr=valueStr.left(valueStr.length()-1);
    fieldStr+=")";
    valueStr+=")";
    queryStr+=fieldStr+" "+valueStr;
    qDebug()<<"add_data:"+queryStr;
    if(!query.exec(queryStr))
    {
        qCritical()<<"sql语句添加数据失败:"+query.lastError().text();
        return -1;
    }

    return 0;
}

int sqliteDriver::delData(QString tableName,QString sqlWhere)
{
    //rly 20211022  truncate table 无用。
    Q_UNUSED(sqlWhere);
    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStr="delete from "+tableName;
//    if(sqlWhere.isEmpty())
//        queryStr="truncate table "+tableName;
//    else
//        queryStr+=" "+sqlWhere;
    if(!sqlWhere.isEmpty())
    {
        queryStr+=" "+sqlWhere;
    }
    qDebug()<<"del_data:"+queryStr;
    if(!query.exec(queryStr))
    {
        qCritical()<<"sql语句删除数据失败:"+query.lastError().text();
        return -1;
    }

    return 0;
}

int sqliteDriver::updateData(QString tableName,QHash<QString,QString> data,QString sqlWhere)
{

    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStr="update "+tableName+" ";
    QHash<QString,QString>::iterator it;
    QString setStr="set ";
    for ( it = data.begin(); it != data.end(); ++it )
    {
        setStr+=it.key()+"='"+it.value()+"'";
        setStr+=",";
    }
    setStr=setStr.left(setStr.length()-1);
    queryStr+=setStr;
    if(!sqlWhere.isEmpty())
        queryStr+=" "+sqlWhere;
    qDebug()<<"update_data:"+queryStr;
    if(!query.exec(queryStr))
    {
        qCritical()<<"sql语句更新数据失败:"+query.lastError().text();

        return -1;
    }

    return 0;
}

/*------------------------------------------------------------------------------
*Function: getData
*Brief：查询数据
*Param：tableName--表名 data--查询数据集 sqlWhere--限制条件
*Retval：int--错误码
---------------------------------------------------------------------------------*/
int sqliteDriver::getData(QString tableName,QList<QHash<QString,QString>> &data,QString sqlWhere)
{

    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStr="select * from "+tableName;
    if(!sqlWhere.isEmpty())
        queryStr+=" "+sqlWhere;
    qDebug()<<"get_data:"+queryStr;
    if(!query.exec(queryStr))
    {
        qCritical()<<"sql语句查询数据失败:"+query.lastError().text();

        return -1;
    }
    QSqlRecord rec = query.record();
    data.clear();
    while(query.next())
    {
        QHash<QString,QString> rowData;
        for(int i =0;i<rec.count();i++)
        {
            if(rec.fieldName(i).split("_").contains("date"))
            {
                QDateTime temp = query.value(i).toDateTime();
                rowData[rec.fieldName(i)]=temp.toString("yyyy-MM-dd hh:mm:ss");
            }
            else
                rowData[rec.fieldName(i)]=query.value(i).toString();
        }
        data.append(rowData);
    }

    return 0;
}

//int sqliteDriver::getTempData(QString tableName,QList<QHash<QString,QString>> &data,QString sqlWhere)
//{

//    QSqlQuery query(QSqlDatabase::database("sqlite"));
//    QString queryStr="select * from "+tableName;
//    if(!sqlWhere.isEmpty())
//        queryStr+=" "+sqlWhere;
//    qDebug()<<"get_data:"+queryStr;
//    query.prepare(queryStr);
//    if(!query.exec(queryStr))
//    {
//        qCritical()<<"sql语句查询数据失败:"+query.lastError().text();

//        return -1;
//    }
//    QSqlRecord rec = query.record();
//    data.clear();
//    while(query.next())
//    {
//        QHash<QString,QString> rowData;
//        for(int i =0;i<rec.count();i++)
//        {
//            if (rec.fieldName(i) == "up_limit")
//            {
//                rowData["上限"]=query.value(i).toString();
//            }
//            else if (rec.fieldName(i) == "low_limit")
//            {
//                rowData["下限"]=query.value(i).toString();
//            }
//            else
//            {
//                rowData[rec.fieldName(i)]=query.value(i).toString();
//            }

//        }
//        data.append(rowData);
//    }

//    return 0;
//}

/*------------------------------------------------------------------------------
*Function: getCount
*Brief：查询数量
*Param：tableName--表名 count--查询数量传出变量 sqlWhere--限制条件
*Retval：int--错误码
---------------------------------------------------------------------------------*/
int sqliteDriver::getCount(QString tableName,int &count,QString sqlWhere)
{

    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStr="select count(*) from "+tableName;
    if(!sqlWhere.isEmpty())
        queryStr+=" "+sqlWhere;
    qDebug()<<"get_count:"+queryStr;
    if(!query.exec(queryStr))
    {
       qCritical()<<"sql语句查询数量失败:"+query.lastError().text();

        return -1;
    }
    while(query.next())
    {
        count=query.value(0).toInt();
    }

    return 0;
}
/*------------------------------------------------------------------------------
*Function: addCol
*Brief：在表中添加一列
*Param：tableName--表名 colName--列名称 colAfter--某列之后
*Retval：int--错误码
---------------------------------------------------------------------------------*/

int sqliteDriver::addCol(QString tableName, QString colName, QString colAfter)
{
//    alter table TABLE_NAME add column NEW_COLUMN_NAME varchar(45) not null after COLUMN_NAME;
//    alter table TABLE_NAME add column NEW_COLUMN_NAME varchar(45) not null;
//    UPDATE my_table SET time = CURRENT_TIMESTAMP;
    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStr="alter table "+ tableName + " add column " + colName + " TEXT(255) ";
    if(!colAfter.isEmpty())
    {
        queryStr += "after " + colAfter;
    }

    qDebug() << "queryStr: " << queryStr;
    if(!query.exec(queryStr))
    {
       qCritical()<<"sql语句查询数量失败:"+query.lastError().text();

        return -1;
    }

    queryStr.clear();
    queryStr += "UPDATE "+ tableName +" SET " + colName + " = 0";
    if(!query.exec(queryStr))
    {
       qCritical()<<"sql语句查询数量失败:"+query.lastError().text();

        return -1;
    }

    return 0;
}

/*------------------------------------------------------------------------------
*Function: getTableHeaders
*Brief：获取所有表头
*Param：tableName--表名 slHeaders--OUT 表头
*Retval：int--错误码
---------------------------------------------------------------------------------*/
int sqliteDriver::getTableHeaders(QString tableName, QStringList &slHeaders)
{
    QSqlQuery query(QSqlDatabase::database("sqlite"));
    QString queryStr="select * from "+tableName;
    if(!query.exec(queryStr))
    {
       qCritical()<<"sql语句查询数量失败:"+query.lastError().text();
        return -1;
    }
    QSqlRecord sqlRecord(query.record());
    for(int i = 0; i < sqlRecord.count(); i++)
    {
        slHeaders << sqlRecord.fieldName(i);
    }
    return 0;
}

