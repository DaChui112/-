#ifndef RS232COMTHREADLIS_H
#define RS232COMTHREADLIS_H


/*-------------------------------串口通讯模块底层读写控制接口实现代码--------------------------------*/


#include <QThread>
#include <stdio.h>
#include <QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include "RS232ComThread.hpp"


class RS232ComThreadLis:public QObject
{
    Q_OBJECT

signals:
    /*已经发送*/
    void RS232BytesWritten(const qint64 &bytes);
    void RS232ReadyRead(const QByteArray &data);

private:


    /*串口配置参数文件名*/
    QString ConfigFile;

public:
    /*串口配置参数结构体*/
    RS232SETTINGS setting;
    /*串口类实例化对象*/
    QSerialPort *serial;

    /*构造函数，传入串口配置ini文件*/
    RS232ComThreadLis(QString configfile,QObject *parent = 0);

    /*开启串口*/
    int RS232ComOpen();

    /*关闭串口*/
    void RS232ComClose();

    /*重新读取串口配置文件*/
    int UpdateComConfig(QString configfile);

    /*获取当前计算机串口列表*/
    QStringList GetCommInfor();

    /*通过配置文件读取串口名称*/
    QString GetRS232Name();

    /*重新设置串口名称并更新到配置文件中*/
    int SetRS232Name(QString name);

    /*通过串口接收数据*/
    QByteArray RS232ComRead();

    /*通过串口发送数据*/
    int RS232ComWrite(QByteArray array);

public slots:
    /*串口写过程信号槽*/
    void handleBytesWritten(qint64 bytes);

    /*串口读过程信号槽*/
    void handleReadyRead();

    /*其他位置调用的写接口信号槽*/
    void handleSendSerialData(const QByteArray &data);

    void setSerialPort(QString com);
};




#endif // RS232COMTHREADLIS_H
