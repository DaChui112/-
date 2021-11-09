#ifndef DIAEDITTESTSHOW_H
#define DIAEDITTESTSHOW_H

#include <QDialog>
#include <QSet>

namespace Ui {
class DiaEditTestShow;
}

class sqlhelper;
class shared_ptr;
class QTableWidget;
class QTableWidgetItem;

class DiaEditTestShow : public QDialog
{
    Q_OBJECT

public:
    explicit DiaEditTestShow(QWidget *parent = nullptr);
    ~DiaEditTestShow();

private:
    void Init();
    void UpdateParameter();                       // 更新参数列表
    void AddTableItem(QTableWidget* tab, const QString& strParameter);// 向列表添加数据
    void DelTableItem(QTableWidget* tab, const QString& strParameter);// 删除列表数据

private slots:
    void slot_pushButton_AddTest_clicked();         // 新增测试项目
    void slot_pushButton_DelTest_clicked();         // 删除测试项目
    void slot_pushButton_Apply_clicked();           // 应用设置
    void slot_pushButton_Cancel_clicked();          // 取消设置
    void slot_pushButton_Add_clicked();             // 启用参数
    void slot_pushButton_Del_clicked();             // 关闭参数

private:
    sqlhelper *db;                                // 数据库操作类
    QList<QHash<QString,QString>> m_parameter_info; // 所有显示参数
    QSet<QString> m_sParameter;                     // 参数名称
    QList<QHash<QString, QString>> m_protocol;    // 参数对应协议问题。

    Ui::DiaEditTestShow *ui;
};

#endif // DIAEDITTESTSHOW_H
