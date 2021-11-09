#include "sqlhelper.h"
#include <QMessageBox>
#include <QDebug>

sqlhelper::sqlhelper()
{
    if(0 != m_db.openSqliteFile("cfg"))
    {
        QMessageBox::warning(nullptr, "警告", "数据库文件打开失败！");
        return;
    }
}

sqlhelper *sqlhelper::getSingleton()
{
    static sqlhelper sqlhelper;
    return &sqlhelper;
}

/**
 * @brief sqlhelper::getItemData
 * @param data
 * @return -1 错误， 0 正常
 * 获取item_parameter表中的所有数据
 */
int sqlhelper::getItemData(QList<QHash<QString,QString>> &data)
{
    return m_db.getData("item_parameter",data, "");
}

/**
 * @brief sqlhelper::addColToItem
 * @param colName  插入列的名称
 * @param colAfter 插入某列之前，若为空则在末尾插入
 * @return -1 错误， 0 正常
 * 在item_parameter中插入一列。
 */
int sqlhelper::addColToItem(const QString &colName, const QString &colAfter)
{
    return m_db.addCol("item_parameter", colName, colAfter);
}

/**
 * @brief sqlhelper::delColToItem
 * @param sParametes
 * @return -1 错误， 0 正常
 * 删除一列。（删除原表新建表）
 */
int sqlhelper::delColToItem(QSet<QString> sParametes)
{
    // 备份保存一份原数据
    QList<QHash<QString,QString>> Itemdata;
    if(-1 == getItemData(Itemdata))
    {
        qDebug() << "getItemData Error";
        return -1;
    }
    // 查询删除列
    QStringList lsHeaders;
    if(-1 == getItemHeaders(lsHeaders))
    {
        qDebug() << "getItemHeaders Error";
        return -1;
    }
    QStringList delstr;
    for(int i = 2; i < lsHeaders.size(); i++)
    {
        if(!sParametes.contains(lsHeaders[i]))
        {
            delstr.append(lsHeaders.at(i));
            lsHeaders.removeAt(i);
        }
    }
    // 删除表格
    if(-1 == delTable("item_parameter"))
    {
        qDebug() << "delTable Error";
        return -1;
    }
    // 创建表格
    if(-1 == createTable("item_parameter", lsHeaders))
    {
        qDebug() << "createTable Error";
        return -1;
    }
    // 将删除的列的键值对删除 并将原数据存入
    for(auto hash: Itemdata)
    {
        for(auto str: delstr)
        {
            hash.remove(str);
        }
        addData("item_parameter", hash);
    }
    return 0;
}

/**
 * @brief sqlhelper::getItemHeaders
 * @param slHeaders OUT
 * @return -1 错误， 0 正常
 * 获取item_parameter的所有表头
 */
int sqlhelper::getItemHeaders(QStringList &slHeaders)
{
    if(0 != m_db.getTableHeaders("item_parameter", slHeaders))
    {
        qDebug() << "getItemHeaders 数据库错误!";
        return -1;
    }
    slHeaders.erase(slHeaders.begin(), (++(++slHeaders.begin())));
    slHeaders.insert(0, "项目代号");
    slHeaders.insert(0, "项目");
    return 0;
}

/**
 * @brief sqlhelper::getAllParameters
 * @param data
 * @return -1 错误， 0 正常
 * 获取参数开启关闭信息
 */
int sqlhelper::getAllParameters(QList<QHash<QString, QString>>& data)
{
    return m_db.getData("parameter_enable",data, "");
}

/**
 * @brief sqlhelper::updateparameter_enable
 * @param data
 * @return -1 错误， 0 正常
 * 更新参数开启关闭状态
 */
int sqlhelper::updateparameter_enable(QList<QHash<QString, QString> > &data)
{
    if(0 != m_db.delData("parameter_enable", ""))
    {
        qDebug() << "delete parameter_enable Error";
        return -1;
    }
    foreach (auto hash, data) {
        if(0 != m_db.addData("parameter_enable", hash))
        {
            qDebug() << "updateparameter_enable is Error";
            return -1;
        }
    }
    return 0;
}
