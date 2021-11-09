/*-------------------------------串口通讯模块用户接口实现代码--------------------------------*/

#include "Tools/RS232Com/RS232ComUserDeal.hpp"

RS232ComUserDeal::RS232ComUserDeal(QObject *parent)
        : QThread(parent)
{
    sendok = true;
    sendokLis = true;
    quit = false;

    /*初始化信号锁*/
    QMutexLocker receiveDatalocker(&receiveDatamutex);
    QMutexLocker sendCommandlocker(&sendCommandmutex);

    /*启动线程开始解析工作*/
    if (!isRunning())
    {
        start();
    }
}

RS232ComUserDeal::~RS232ComUserDeal()
{
    receiveDatamutex.lock();
    quit = true;
    receiveDatamutex.unlock();
    wait();
    msleep(100);
}

void RS232ComUserDeal::run()
{
    while(!quit)
    {
        /*发送任务处理*/
        sendCommandmutex.lock();

        if((sendok)&&(listSend.size()))
        {
            QByteArray cmd;
            cmd = (QByteArray)listSend.at(0);
            emit SendUserData(cmd);
            sendok = false;
        }

        if((sendokLis)&&(listSendLis.size()))
        {
            QByteArray cmd;
            cmd = (QByteArray)listSendLis.at(0);
            emit SendUserDataLis(cmd);
            sendokLis = false;
        }

        sendCommandmutex.unlock();


        /*接收队列处理*/
        receiveDatamutex.lock();

        if(listReceive.size())
        {
            /*将接收到的数据发送出去，有用户层处理*/
            QByteArray data;
            data = (QByteArray)listReceive.at(0);
            emit SendReceivedData(data);
            listReceive.removeAt(0);
        }

        if(listReceiveLis.size())
        {
            /*将接收到的数据发送出去，有用户层处理*/
            QByteArray data;
            data = (QByteArray)listReceiveLis.at(0);
            emit SendReceivedDataLis(data);
            listReceiveLis.removeAt(0);
        }
        receiveDatamutex.unlock();
        msleep(10);
    }
}


/*用户数据入队列处理*/
void RS232ComUserDeal::AddSendCommand(const QByteArray &command)
{
    /*将用户层数据入发送命令队列*/
    sendCommandmutex.lock();
    this->listSend.append(command);
    sendCommandmutex.unlock();
}

/*用户数据入队列处理*/
void RS232ComUserDeal::AddSendCommandLis(const QByteArray &command)
{
    /*将用户层数据入发送命令队列*/
    sendCommandmutex.lock();
    this->listSendLis.append(command);
    sendCommandmutex.unlock();
}

/*收到串口数据帧处理*/
void RS232ComUserDeal::handleReceivedSerialDataOK(const QByteArray &data)
{
    receiveDatamutex.lock();
    this->listReceive.append(data);
    receiveDatamutex.unlock();
}

/*收到串口数据帧处理Lis*/
void RS232ComUserDeal::handleReceivedSerialDataOKLis(const QByteArray &data)
{
    receiveDatamutex.lock();
    this->listReceiveLis.append(data);
    if(data.at(0)!='A')
    {
//        int asd=0; //rly 20211104 该变量未使用
    }
    receiveDatamutex.unlock();
}

/*完成用户数据发送处理*/
void RS232ComUserDeal::handleSerialDataSendOK()
{
    /*移除当前已经发送的数据*/
    sendCommandmutex.lock();
    if(listSend.size())
        this->listSend.removeAt(0);


    /*准备下发下一个*/
    sendok = true;
    sendCommandmutex.unlock();
}

/*完成用户数据发送处理*/
void RS232ComUserDeal::handleSerialDataSendOKLis()
{
    /*移除当前已经发送的数据*/
    sendCommandmutex.lock();
    this->listSendLis.removeAt(0);


    /*准备下发下一个*/
    sendokLis = true;
    sendCommandmutex.unlock();
}
