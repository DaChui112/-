#include "communicationTcp.h"
#include <QSettings>
#include <QTextCodec>

CommunicationTcp::CommunicationTcp(QObject *parent): QThread(parent)
{
    timer = new QTimer(this);
    tcpServer = new QTcpServer(this);
    tcpClient = new QTcpSocket(this);
    connect(this,SIGNAL(signalQuitThread()),this,SLOT(slotQuitThread()));
    this->moveToThread(this);
    this->start();

}


CommunicationTcp::~CommunicationTcp()
{
    emit signalQuitThread();
    this->wait();
    delete tcpServer;
    delete tcpClient;
}


//退出线程
void CommunicationTcp::slotQuitThread()
{
    this->closeTcp();
    if(timer->isActive())
    {
        timer->stop();
    }
    delete  timer;
    this->quit();
}


void CommunicationTcp::run()
{
    QString threadStr = "Tcp线程："+ QString::number((unsigned long)QThread::currentThreadId());
    qDebug() << QThread::currentThread();
    connect(timer,SIGNAL(timeout()),this,SLOT(slotTimeOut()));
    this->exec();
}


QString CommunicationTcp::getConfigPath()
{
    return this->configPath;
}


CommunicationTcp::TcpMode CommunicationTcp::getTcpMode()
{
    return this->tcpMode;
}


QString CommunicationTcp::getIpAdress()
{
    return this->ipAdress;
}


QString CommunicationTcp::getPort()
{
    return this->port;
}


QStringList CommunicationTcp::getClientsIp()
{
    QStringList ipReturn;
    for(int i=0;i<clients.size();i++)
    {
        ipReturn.append(clients.at(i)->peerAddress().toString().remove("::ffff:"));
    }
    return ipReturn;
}

QString CommunicationTcp::getErrorString()
{
    return this->errorString;
}


void CommunicationTcp::setConfigPath(const QString &configPath)
{
    this->configPath=configPath;
}


void CommunicationTcp::setTcpMode(const TcpMode &tcpMode)
{
    this->tcpMode=tcpMode;
}


void CommunicationTcp::setServerInformation(const QString &ipAdress,const QString &port)
{
    if(!configPath.isEmpty())
    {
        QSettings settings(this->configPath,QSettings::IniFormat);
        settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
        settings.setValue("tcp/ip", ipAdress);
        settings.setValue("tcp/port", port);
    }
    else
    {
        this->ipAdress=ipAdress;
        this->port=port;
    }
}


void CommunicationTcp::setClientInformation(const QString &port)
{
    if(!configPath.isEmpty())
    {
        QSettings settings(this->configPath,QSettings::IniFormat);
        settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
        settings.setValue("tcp/port", port);
    }
    else
        this->port=port;
}


bool CommunicationTcp::openTcp()
{    
    if(tcpMode == Server)
    {
        if(port.isEmpty())
        {
            errorString.clear();
            errorString.append("port is empty , tcp open failed!");
            return false;
        }
        connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptClientConnect()));
        if(tcpServer->isListening())
            return true;
        tcpServer->listen(QHostAddress::Any,port.toInt());
        return true;
    }
    else if(tcpMode == Client)
    {
        if(port.isEmpty()||ipAdress.isEmpty())
        {
            errorString.clear();
            errorString.append("port or ipAdress is empty , tcp open failed!");
            return false;
        }
        connect(tcpClient,SIGNAL(connected()),this,SLOT(tcpConnected()));
        connect(tcpClient,SIGNAL(disconnected()),this,SLOT(tcpDisConnected()));
        connect(tcpClient,SIGNAL(readyRead()),this,SLOT(tcpReadAll()));
        tcpClient->connectToHost(ipAdress,port.toInt());
        if(!tcpClient->waitForConnected(RECONNECT))
        {
            if(!timer->isActive())
                timer->start(RECONNECT);
        }
        return true;
    }
    return false;
}


void CommunicationTcp::closeTcp()
{
    if(tcpMode == Server)
    {
        for(int i=0;i<clients.count();i++)
        {
            clients.at(i)->disconnect();
            clients.at(i)->close();
        }
        qDeleteAll(clients);
        clients.clear();
        tcpServer->disconnect();
        tcpServer->close();
    }
    else
    {
        tcpClient->disconnect();
        if(tcpClient->isOpen())
            tcpClient->close();
    }
}


void CommunicationTcp::tcpDisConnected()
{
    QTcpSocket *tcpStock = (QTcpSocket*)sender();
    QString ipAccpet = tcpStock->peerAddress().toString().remove("::ffff:");
    //qDebug()<<"Tcp DisConnected:"<<ipAccpet;
    if(tcpMode == Server)
    {
        int index = clients.indexOf(tcpStock);
        clients.remove(index);
        tcpStock->disconnect();
        tcpStock->deleteLater();
        if(clients.isEmpty())
            emit tcpAllDisConnected();
        emit acceptConnectNumChanged(clients.size());
    }
    else
    {
        if(!timer->isActive())
            timer->start(RECONNECT);
        emit tcpAllDisConnected();
    }
}


void CommunicationTcp::acceptClientConnect()
{
   QTcpSocket *accpetStock = tcpServer->nextPendingConnection();
   connect(accpetStock,SIGNAL(readyRead()),this,SLOT(tcpReadAll()));
   connect(accpetStock,SIGNAL(disconnected()),this,SLOT(tcpDisConnected()));
   clients.append(accpetStock);
   QString ipAccpet = accpetStock->peerAddress().toString().remove("::ffff:");
   //qDebug()<<"accept client connect:"<<ipAccpet;
   emit acceptConnectNumChanged(clients.size());
}


void CommunicationTcp::tcpConnected()
{
    if(timer->isActive())
        timer->stop();
    emit connectedServer();
    //qDebug()<<"connected server:"<<ipAdress<<port;
}


void  CommunicationTcp::tcpReadAll()
{
    QTcpSocket *tcpStock = (QTcpSocket*)sender();
    qint64 count = tcpStock->bytesAvailable();
    QByteArray revData;
    if(count > 0)
    {

        revData = tcpStock->read(count);
        qDebug()<<QString(revData.toHex());
        if(!revData.isEmpty())
            emit tcpReceived(revData);
    }
}


void CommunicationTcp::slotTimeOut()
{
    tcpClient->abort();
    tcpClient->connectToHost(ipAdress,port.toInt());
}


void CommunicationTcp::slotTcpWrite(const QByteArray &data_write)
{
    if(tcpMode == Server)
    {
        if(clients.isEmpty())
        {
            errorString.clear();
            errorString.append("serialport 发送失败!\n");
            errorString.append("serialport 关闭了!");
            return;
        }
        for(int i=0;i<clients.count();i++)
        {
            if(clients.at(i)->state() == QTcpSocket::ConnectedState)
            {
                clients.at(i)->write(data_write);
                if(!clients.at(i)->waitForBytesWritten(WRITEWAIT))
                {
                    errorString.clear();
                    errorString.append("tcpServer 发送失败!\n");
                    errorString.append(clients.at(i)->errorString());
                }
            }
        }
    }
    else
    {
        if(tcpClient->state() == QTcpSocket::ConnectedState)
        {
            tcpClient->write(data_write);
            if(!tcpClient->waitForBytesWritten(WRITEWAIT))
            {
                errorString.clear();
                errorString.append("tcpClient 发送失败!\n");
                errorString.append(tcpClient->errorString());
            }
        }
        else
        {
            errorString.clear();
            errorString.append("tcpClient 发送失败!\n");
            errorString.append("tcpClient 关闭了!");
            //DebugLog(logger,"TCP error:" + errorString);
        }

    }
}

//IP,端口发生变化
void CommunicationTcp::slotTcpPortChange()
{
    closeTcp();
    openTcp();
}

//打开Tcp
void CommunicationTcp::slotOpenTcp(QString ip, QString port, int tcpMode)
{
    //setConfigPath(configPath);
    closeTcp();
    this->ipAdress = ip;
    this->port = port;
    if(tcpMode == 0)
        setTcpMode(Server);
    else
        setTcpMode(Client);
    openTcp();
}
