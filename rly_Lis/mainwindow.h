#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spdlog/sinks/rotating_file_sink.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class RS232ComThread;
class RS232ComProtocal;
class RS232ComUserDeal;
class RS232ComThreadLis;
class sqlhelper;
class CommunicationTcp;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_btn_SerialOpen_clicked();     // 打开/关闭串口
    void slot_btn_Listen_clicked();         // 打开/关闭监听
    void slot_btn_AddTest_clicked();        // 添加测试项目
    void slot_btn_DeleteTest_clicked();     // 删除测试项目
    void slot_btn_SendTest_clicked();       // 下发实验数据
    void slot_btn_Edit_clicked();           // 编辑项目参数
    void slot_btn_ClearTestResult_clicked();// 清空实验结果
    void slot_btn_AddSample_clicked();      // 添加样本号
    void slot_btn_DeleteSample_clicked();   // 删除样本号
    void slot_tableWidget_Test_cellDoubleClicked(int row, int column);    // 编辑当前项目
    void slot_tableWidget_Test_cellClicked(int row, int column);          // 切换选中
    void slot_tableWidget_sampleNo_currentCellChanged(int,int,int,int);   // 切换样本后刷新
    void slot_logTimer();                   // 日志流刷新
    void slot_LisReceive_Paser(QByteArray data); // LIS回复

private:
    void Init();
    void GetCommInfor(QStringList &slcoms, QStringList &slComIp);       // 获取串口列表
    void UpdataTestData();                       // 更新项目数据
    void UpdateSamples();                        // 更新样本号
    void SendCommendData();                      // 发送样本数据
    void SendData(QByteArray& command);          // 判断发送方式

signals:
    void signalOpenTcp(QString,QString,int);
    void signalCloseTcp();
    void signalSendPcData(QByteArray);

private:
    RS232ComThread *RS232Thread;                 // 串口底层操作接口类
    RS232ComProtocal *RS232Protocal;             // 串口通讯协议操作类
    RS232ComUserDeal *RS232User;                 // 串口用户操作接口类
    RS232ComThreadLis *RS232ThreadLis;           // Lis串口底层操作接口类
    CommunicationTcp *tcpListen;                 // TCP操作类

    std::shared_ptr<spdlog::logger> m_rotating_logger; // 日志
    QTimer *m_timer;                               // 日志刷新定时器
    sqlhelper *m_db;                               // 数据库操作类
    QString m_strCurrentSampleNo;                // 当前样本号
    QHash<QString, QSet<QString>> m_SampleData;  // 样本号及其对应的开启试剂

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
