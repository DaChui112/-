#ifndef RS232COMPROTOCAL_H
#define RS232COMPROTOCAL_H


/*-------------------------------串口通讯模块通讯协议实现代码--------------------------------*/
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QList>
#include <QTimer>

/*--------------------------------------------------------
 * 通讯协议格式： STX1 STX2 PKL Motor CMD DATA CHK
 --------------------------------------------------------*/
/*主设备发送帧头*/
#define MAIN_STX1                   0xFF
#define MAIN_STX2                   0xAA

/*主设备接收尾*/
#define MAIN_RTX1                   0xBB

/*从设备发送帧头*/
#define SLAVE_STX1                  0xFF
#define SLAVE_STX2                  0xEE

/*从设备接收尾*/
#define SLAVE_RTX1                  0xDD

/*应答通讯协议*/
#define ACK_FRAME_LENGTH             3

/*应答正确*/
#define ACK_OK_1                    0xAA
#define ACK_OK_2                    0xBB
#define ACK_OK_3                    0xCC

/*应答错误*/
#define ACK_ERROR_1                 0xDD
#define ACK_ERROR_2                 0xEE
#define ACK_ERROR_3                 0xFF

/*当DATA字段为0时，数据帧长度为7*/
#define PROTOCAL_MIN_LENGTH         7

/*超时重新发送命令次数*/
#define RESEND_MAX_TIME             3

/*等待应答超时，500ms*/
#define WAIT_ACK_TIMEOUT            500

/*一帧数据接收过程中，如果超过1秒接收数据长度不变并且还未接收完整，则清除当前接收到的数据*/
#define WAIT_COMPLETE_FRAME_TIMEOUT 10000

/*是否进行校验和应答的控制宏*/
#define COMMAND_CHECK_CONTROL       0

/*是否开启等待应答超时机制*/
#define COMMAND_ACK_CHECK_CONTROL   0

/*等待应答数据超时时间，5表示500ms*/
#define ACK_TIMEOUT_TIME            5

/*通讯异常检测次数*/
#define COMMUNICATION_CHECK_ERROR_COUNT 3

/*Lis发送接收帧头*/
#define LIS_STX                   0x02

/*Lis发送接收帧尾*/
#define LIS_RTX                   0x03


/*通讯工作模式*/
enum WorkMode
{
    WorkMode_None = 0,
    WorkMode_PC_TO_MAINBOARD,   /*电脑对主控板间的通讯*/
    WorkMode_PC_TO_MOTOR        /*电脑对电机驱动板间的通讯*/
};

/*发送命令过程状态*/
enum CommandSendStatus
{
    Send_Status_Idle = 0,
    Send_Status_Sending,
    Send_Status_Waiting_ACK,
    Send_Status_Timeout_Resend,
    Send_Status_ACK_ERROR_Resend,
    Send_Status_ACK_OK,
    Send_Status_ACK_SEND,
    Send_Status_OK,
    Send_Status_Error
};


class RS232ComProtocal : public QThread
{
    Q_OBJECT

public:
    RS232ComProtocal(QObject *parent = 0);
    ~RS232ComProtocal();
    int SendCommand(QByteArray data);
    void run();
    /*设置当前软件工作模式*/
    void SetWorkMode(WorkMode mode);
    /*保存当前工作模式*/
    WorkMode workmode;
    uint8_t SendFlagB;
signals:

    /*请求串口数据发送信号*/
    void SendSerialData(const QByteArray &data);

    void SendSerialDataLis(const QByteArray &data);

    /*串口数据发送完成信号*/
    void SerialDataSendOK(void);
    void SerialDataSendOKLis();

    /*接收一帧完整数据信号*/
    void ReceivedSerialDataOK(const QByteArray &data);

    void ReceivedSerialDataOKLis(const QByteArray &data);

#if COMMAND_ACK_CHECK_CONTROL
    /*串口异常型号*/
    void RS232CommunicationError(void);
#endif

private:


    /*发送线程发送状态*/
    CommandSendStatus sendstatus;

    CommandSendStatus sendstatusLis;

    /*命令发送次数*/
    int CommandSendTime;

    /*保存当前发送的数据*/
    QByteArray writeData;

    QByteArray writeDataLis;

    /*保存应答命令*/
    QByteArray writeACK;
    QList <QByteArray> ackList;

    /*当前写的是命令还是应答数据1：发送数据   2：应答命令*/
    int currentWriteType;

    /*记录当前已经发送的字节数*/
    qint64 bytesWritten;

    qint64 bytesWrittenLis;

    /*保存当前已经收到的串口数据*/
    QByteArray readData;

    QByteArray readDataLis;

    /*查询串口数据是否发送完成*/
    bool isDataWrittenOK();

    /*超时或应答错误重新发送*/
    void ReSendCommand(int resendtype);

    /*命令发送流程控制*/
    void SendCommandFlow();

    /*命令接收流程控制*/
    void ReceivedCommandDealFlow(QByteArray data,uint8_t xorcheck);

    /*异或校验*/
    uint8_t GetXorCheckValue(QByteArray data);

    /*用协议封装发送数据*/
    QByteArray AddProtocalShell(QByteArray data);
    QByteArray AddProtocalShellLis(QByteArray data);

    /*去掉接收数据的协议外壳*/
    QByteArray RemoveProtocalShell(QByteArray data);

    /*命令发送过程变量*/
    int waitTimeout;

    /*串口接收数据缓存访问锁*/
    QMutex readDatamutex;

    /*串口已经发送字节数访问锁*/
    QMutex writtenBytesmutex;

    /*是否退出线程处理*/
    bool quit;

    /*是否需要协议层校验*/
    bool needXORCheck;

    void SendCommandFlowLis();
    void ReceiveCommandFlowLis(int &,qint64 &);

#if COMMAND_ACK_CHECK_CONTROL
    /*通讯异常计数器*/
    uint32_t communicationErrorCount;

    /*等待应答命令超时计数器*/
    uint32_t ackTimeoutCount;

    /*等待应答命令定时器*/
    QTimer *ackTimeoutTimer;

#endif

public slots:

    /*处理从串口新接收到的数据*/
    void handleSerialDataReceived(const QByteArray &data);
    void handleSerialDataReceivedLis(const QByteArray &data);

    /*处理已经从串口发送出去的数据*/
    void handleSerialDataWritten(qint64 bytes);

    /*从用户接收用户数据发送信号的处理*/
    void handleUserCommandSend(const QByteArray &data);

    void handleUserCommandSendLis(const QByteArray &data);


#if COMMAND_ACK_CHECK_CONTROL
    void ackTimerUpdate();
#endif
};


#endif // RS232COMPROTOCAL_H
