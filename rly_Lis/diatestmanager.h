#ifndef DIATESTMANAGER_H
#define DIATESTMANAGER_H

#include <QDialog>
#include <unordered_map>

namespace Ui {
class diaTestManager;
}

class sqlhelper;
class QComboBox;

class diaTestManager : public QDialog
{
    Q_OBJECT

public:
    explicit diaTestManager(QVector<QPair<QString, QString>> allParas, QString strName = "", QString strCode = "",  QWidget *parent = nullptr);;
    ~diaTestManager();

private slots:
    void slot_pushButton_Apply_clicked();
    void slot_pushButton_Cancel_clicked();

private:
    void Init();
    void InitData();
    void getComboxData(QHash<QString, QString>& hsParas);           // 获取各个参数数据
    void getAllPorotocol(QSet<int> &sNumber);

private:
    QFont m_ft1;
    QString m_strName;                              // 名称
    QString m_strCode;                              // 代号
    QVector<QPair<QString, QString>> m_allParas;    // 存储传入的表头及数据
    QHash<QString, QComboBox*> m_data;              // 保存了table页中字段与combobox
    sqlhelper* m_db;

    Ui::diaTestManager *ui;
};

#endif // DIATESTMANAGER_H
