#ifndef SQLHELPER_H
#define SQLHELPER_H
#include "Tools/Sqlite/sqlitedriver.hpp"

class sqlhelper : public sqliteDriver
{
public:
    static sqlhelper* getSingleton();
    int getItemData(QList<QHash<QString, QString> > &data);             // 获取项目列表
    int addColToItem(const QString& colName, const QString& colAfter);  // 添加一行
    int delColToItem(QSet<QString> sParametes);                         // 删除一行（将原表删除后重新建表）
    int getItemHeaders(QStringList &slHeaders);                         // 获取表头
    int getAllParameters(QList<QHash<QString, QString>>& data);         // 获取参数启用表
    int updateparameter_enable(QList<QHash<QString, QString>>& data);   // 更新参数启用表

private:
    sqlhelper();
    sqlhelper(const sqlhelper&) = delete;
    sqlhelper& operator=(const sqlhelper&) = delete;

private:
    sqliteDriver m_db;
};

#endif // SQLHELPER_H
