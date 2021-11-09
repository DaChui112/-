#ifndef RS232COMUSERDEAL_H
#define RS232COMUSERDEAL_H

/*-------------------------------串口通讯模块用户接口实现代码--------------------------------*/
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QList>
#include <QDebug>
class RS232ComUserDeal : public QThread
{
    Q_OBJECT

public:
    RS232ComUserDeal(QObject *parent = 0);
    ~RS232ComUserDeal();
    void run();

signals:

    /*请求串口数据发送信号*/
    void SendUserData(const QByteArray &data);

    /*将接收到的数据帧发送给用户层*/
    void SendReceivedData(const QByteArray &data);

    /*请求Lis串口数据发送信号*/
    void SendUserDataLis(const QByteArray &data);

    /*将接收到Lis的数据帧发送给用户层*/
    void SendReceivedDataLis(const QByteArray &data);

private:

    /*线程退出标识*/
    bool quit;

    /*发送完成标识*/
    bool sendok;
    bool sendokLis;

    /*用户数据队列*/
    QList<QByteArray> listSend;

    /*接收数据队列*/
    QList<QByteArray> listReceive;

    /*Lis用户数据队列*/
    QList<QByteArray> listSendLis;

    /*Lis接收数据队列*/
    QList<QByteArray> listReceiveLis;



    /*接收数据帧存访问锁*/
    QMutex receiveDatamutex;

    /*发送命令访问锁*/
    QMutex sendCommandmutex;

public slots:
    /*收到串口数据帧处理*/
    void handleReceivedSerialDataOK(const QByteArray &data);

    /*完成用户数据发送处理*/
    void handleSerialDataSendOK();

    /*用户数据入队列处理*/
    void AddSendCommand(const QByteArray &command);

    /*Lis收到串口数据帧处理*/
    void handleReceivedSerialDataOKLis(const QByteArray &data);

    /*Lis完成用户数据发送处理*/
    void handleSerialDataSendOKLis();

    /*Lis用户数据入队列处理*/
    void AddSendCommandLis(const QByteArray &command);

};

#endif // RS232COMUSERDEAL_H
