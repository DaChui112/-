#ifndef COMMUNTICATIONTCP_H
#define COMMUNTICATIONTCP_H

#include <QObject>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QMutex>

#define WRITEWAIT 1000      //TCP等待时间
#define RECONNECT 1000      //超时重连时间


class CommunicationTcp : public QThread
{
    Q_OBJECT
public:
    enum TcpMode {
        Server = 0,
        Client
    };

    explicit CommunicationTcp(QObject *parent = 0);
    ~CommunicationTcp();

private:
    QTimer *timer=0;          //定时器
    QTimer *tcpReConnectTimer = 0;       //tcp重连定时器
    QString configPath;              //tcp配置存储路径
    TcpMode tcpMode;                 //tcp模式 Server--服务端  Client--客户端
    QString ipAdress;                //tcp通信Ip地址
    QString port;                    //tcp通信端口
    QTcpServer *tcpServer;           //tcp服务端操作
    QTcpSocket *tcpClient;           //tcp客户端操作
    QVector<QTcpSocket*> clients;    //缓存所有连接请求的客户端
    QString errorString;             //错误信息字符串

private:
    void run();                                         //线程执行函数
private slots:
    void slotQuitThread();  //退出线程
    void slotTimeOut();     //定时器槽
signals:
    void signalQuitThread();        //退出线程
private slots:
    void acceptClientConnect(); //监听到客户端连接信号
    void tcpConnected();        //客户端连接到服务端处理
    void tcpDisConnected();     //客户端掉线处理
    void tcpReadAll();          //tcp读取数据
    //void tcpReConnectTimerOut();   //重连槽
    void setConfigPath(const QString &configPath);                          //设置配置存储路径
    void setTcpMode(const TcpMode &tcpMode);                                //设置tcp模式
    void setServerInformation(const QString &ipAdress,const QString &port); //设置服务端端口
    void setClientInformation(const QString &port);                         //设置客户端端口

    bool openTcp();  //打开tcp
    void closeTcp(); //关闭tcp


    QString getConfigPath();    //获取配置存储路径
    TcpMode getTcpMode();       //获取当前tcp使用类型 server--服务端 client--客户端
    QString getIpAdress();      //获取当前使用的ip地址
    QString getPort();          //获取当前使用的端口号
    QStringList getClientsIp(); //获取所有已连接的客户端Ip
    QString getErrorString();   //获取操作错误信息
public:


public slots:
    void slotTcpWrite(const QByteArray &data_write);           //tcp写入数据
    void slotTcpPortChange();                                  //IP,端口发生变化
    void slotOpenTcp(QString ip, QString port, int tcpMode);   //打开Tcp

signals:
    void acceptConnectNumChanged(int connectNum);       //服务端客户端连接数量发生变化
    void connectedServer();                             //客户端已连接到服务端信号
    void tcpAllDisConnected();                          //掉线信号，服务端为所有掉线
    void tcpReceived(const QByteArray &data_reveive);   //tcp接收到数据并发送解析信号
};

#endif // COMMUNTICATIONTCP_H
