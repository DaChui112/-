/*-------------------------------串口通讯模块通讯协议实现代码--------------------------------*/
#include "Tools/RS232Com/RS232ComProtocal.hpp"
#include "Tools/RS232Com/RS232ComThread.hpp"
#include <QDebug>

QT_USE_NAMESPACE

/*构造函数*/
RS232ComProtocal::RS232ComProtocal(QObject *parent)
    : QThread(parent)
{
    /*默认和主控电路板通讯*/
    workmode = WorkMode_PC_TO_MAINBOARD;
    needXORCheck = true;
    if(COMMAND_CHECK_CONTROL == 0)
    {
        needXORCheck = false;
    }

    /*线程开始运行*/
    quit = false;

    /*默认没有进行数据发送*/
    sendstatus = Send_Status_Idle;
    sendstatusLis = Send_Status_Idle;
    SendFlagB = 0;

    /*初始化信号锁*/
    QMutexLocker readDatalocker(&readDatamutex);
    QMutexLocker writtenByteslocker(&writtenBytesmutex);

    waitTimeout = 0;
    bytesWritten = 0;
    currentWriteType = 0;
    writeACK.clear();
    writeData.clear();
    readData.clear();
    ackList.clear();

    /*启动线程开始解析工作*/
    if (!isRunning())
    {
        start();
    }

#if COMMAND_ACK_CHECK_CONTROL

    /*通讯异常计数器次数清零*/
    communicationErrorCount = 0;

    /*等待应答命令超时计数器次数清零*/
    ackTimeoutCount = 0;

    /*等待应答命令定时器初始化*/
    ackTimeoutTimer = new QTimer(this);
    ackTimeoutTimer->connect(ackTimeoutTimer,SIGNAL(timeout()),this,SLOT(ackTimerUpdate()));
    ackTimeoutTimer->start(100);
#endif

}

/*解析函数*/
RS232ComProtocal::~RS232ComProtocal()
{
    readDatamutex.lock();
    quit = true;
    readDatamutex.unlock();
    wait();
    msleep(100);
}


/*接收数据解析及处理*/
void RS232ComProtocal::run()
{
    int getstxflag = 0;
    int last_size = 0;
    int last_size_lis = 0;
    qint64 timeout = 0;
    qint64 timeout_lis = 0;
    QByteArray stx;
    stx.append(SLAVE_STX1);
    stx.append(SLAVE_STX2);

    QByteArray ack_ok;
    ack_ok.append(ACK_OK_1);
    ack_ok.append(ACK_OK_2);
    ack_ok.append(ACK_OK_3);

    QByteArray ack_error;
    ack_error.append(ACK_ERROR_1);
    ack_error.append(ACK_ERROR_2);
    ack_error.append(ACK_ERROR_3);


    while(!quit)
    {
        readDatamutex.lock();
        /*发送控制流程*/
        SendCommandFlow();

        //发送lis数据
        SendCommandFlowLis();
        ReceiveCommandFlowLis(last_size_lis,timeout_lis);

        /*判断是否有完整的一帧数据存在，如果存在则截取数据*/
        getstxflag = 0;
        //        if(needXORCheck)
        //        {
        //            if(readData.size()>= ACK_FRAME_LENGTH)
        //            {
        //                int ack_ok_index = readData.indexOf(ack_ok,0);
        //                int ack_error_index = readData.indexOf(ack_error,0);
        //                int stx_index = readData.indexOf(stx,0);
        //                if((stx_index == -1)&&(ack_ok_index == -1)&&(ack_error_index == -1))
        //                {
        //                    /*没有找到协议头，清空当前接收缓存*/
        //                    readData.clear();
        //                }
        //                else
        //                {
        //                    if(stx_index != -1)
        //                    {

        //                        if(stx_index == 0)
        //                        {
        //                            /*接收正常不处理*/
        //                        }
        //                        else
        //                        {
        //                            if((ack_ok_index == -1)&&(ack_error_index== -1))
        //                            {
        //                                readData.remove(0,stx_index);
        //                            }
        //                        }

        //                        getstxflag = 1;

        //                    }
//                    else if(ack_ok_index != -1)
//                    {
//                       /*应答正确，更改状态*/
//                        //if(sendstatus == Send_Status_Waiting_ACK)
//                        {
//                            sendstatus = Send_Status_ACK_OK;
//                        }
//                        readData.remove(ack_ok_index,ACK_FRAME_LENGTH);
//                    }
//                    else if(ack_error_index != -1)
//                    {
//                        /*应答错误，重新发送*/
//                        //if(sendstatus == Send_Status_Waiting_ACK)
//                        {
//                            sendstatus = Send_Status_ACK_ERROR_Resend;
//                        }
//                        readData.remove(ack_error_index,ACK_FRAME_LENGTH);
//                    }
//                }
//            }
//        }
        if(readData.size() >= 2)
        {
            int stx_index = readData.indexOf(stx,0);
            if(stx_index == -1)
            {
                /*没有找到协议头，清空当前接收缓存*/

                readData.clear();
            }
            else
            {
                if(stx_index == 0)
                {
                    /*接收正常不处理*/
                }
                else
                {
                    readData.remove(0,stx_index);
                }
                getstxflag = 1;
            }
        }

        if((readData.size()>= PROTOCAL_MIN_LENGTH)&&(getstxflag))
        {
            uint length = (uchar)readData.at(2)*256 + (uchar)readData.at(3);
            if(length>0&&length<10000)
            {
                if((uint)readData.size() >= (length + 7))
                {
                    //qDebug()<<readData.at(length+6);
                    if((uchar)readData.at(length+6)==SLAVE_RTX1)
                    {
                        /*截取完整数据帧进行后处理*/
                        QByteArray newFrame;
                        for(uint i=0; i<length;i++)
                        {
                            newFrame.append(readData.at(i+4));
                        }
                        /*对接收到的数据进行校验判断并处理*/
                        ReceivedCommandDealFlow(newFrame,(uint8_t)(readData.at(length+4)));

                        /*将收到的数据截取出来*/
                        readData.remove(0,length+7);
                    }
                    else
                    {
                        readData.remove(0,2);
                    }
                }
            }
            else
            {
                if(length>10000)
                {
                }
                readData.remove(0,2);
            }
        }

        /*还未收到完整帧数据，等待超时，超时10000ms，清空readData*/
        if(last_size)
        {
            timeout++;
            if(timeout >= WAIT_COMPLETE_FRAME_TIMEOUT)
            {
                if(readData.size() == last_size)
                {
                    qDebug()<<__FILE__<<__FUNCTION__<<__LINE__<<"Receive One Frame Timeout,Clear received data."<<readData.toHex();
                    readData.clear();
                    timeout = 0;
                }
            }
        }
        else
        {
            timeout = 0;
        }

        last_size = readData.size();

        readDatamutex.unlock();

        msleep(10);
    }

}

/*查询串口数据是否发送完成*/
bool RS232ComProtocal::isDataWrittenOK()
{
    return true;
//    if(currentWriteType == 1)
//    {
//        if(bytesWritten == writeData.size())
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//    }
//    else if(currentWriteType == 2)
//    {
//        if(bytesWritten == writeACK.size())
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//    }
//    else
//    {
//        return true;
//    }

}

/*发送命令接口，通过信号发送到串口类去发送*/
int RS232ComProtocal::SendCommand(QByteArray data)
{
    QByteArray newdata;

    newdata = AddProtocalShell(data);

    writeData.clear();
    writeData = newdata;
    CommandSendTime = 1;

    return 1;
}

/*超时或应答重新发送命令，resendtype ：1为超时发送，0为应答错误发送*/
void RS232ComProtocal::ReSendCommand(int resendtype)
{
    if(resendtype)
    {
        CommandSendTime += 1;

        /*超时机制处理*/
        if(CommandSendTime > RESEND_MAX_TIME)
        {
            /*串口通讯异常处理*/
        }
    }
    sendstatus = Send_Status_Idle;
}


/*串口发送命令控制流程，按通讯协议的要求执行*/
void RS232ComProtocal::SendCommandFlow()
{
    if(writeData.size())
    {
        bytesWritten = 0;
        emit SendSerialData(writeData);
        QThread::msleep(10);
        sendstatus = Send_Status_OK;
        bytesWritten = 0;
        currentWriteType = 0;
        sendstatus = Send_Status_Idle;
        writeData.clear();
        emit SerialDataSendOK();
    }

//   switch(sendstatus)
//   {
//       case Send_Status_Idle:
            /*判断是否有应答命令需要发送*/
//            if(ackList.count()&&(needXORCheck))
//            {
//                writeACK = QByteArray(ackList.at(0));

//                bytesWritten = 0;
//                emit SendSerialData(writeACK);
//                currentWriteType = 2;
//                sendstatus = Send_Status_ACK_SEND;
//            }
//            if(writeData.size())
//            {
//                bytesWritten = 0;
//                emit SendSerialData(writeData);
//                currentWriteType = 1;
//                //sendstatus = Send_Status_Sending;
//                sendstatus = Send_Status_OK;
//            }
//            break;

//       case Send_Status_Sending:
//            break;

//       case Send_Status_Waiting_ACK:
//            /*等待应答超时处理*/
//#if COMMAND_ACK_CHECK_CONTROL
//            if(ackTimeoutCount >= ACK_TIMEOUT_TIME)
//            {
//                communicationErrorCount++;
//                if(communicationErrorCount >= COMMUNICATION_CHECK_ERROR_COUNT)
//                {
//                    sendstatus = Send_Status_Error;
//                }
//                else
//                {
//                    /*重新发送命令*/
//                    ackTimeoutCount = 0;
//                    sendstatus = Send_Status_Idle;
//                }
//            }
//#endif
//            break;

//       case Send_Status_Timeout_Resend:
//            if(isDataWrittenOK())
//            {
//                ReSendCommand(1);
//            }
//            break;

//       case Send_Status_ACK_ERROR_Resend:
//           if(isDataWrittenOK())
//           {
//                ReSendCommand(0);
//           }
//            break;

//       case Send_Status_ACK_OK:
//            sendstatus = Send_Status_OK;
//            break;

//       case Send_Status_ACK_SEND:
//            /*等待发送完毕*/
//            if(currentWriteType == 2)
//            {
//              if(writeACK.size() == bytesWritten)
//              {

//              }
//            }
//            sendstatus = Send_Status_OK;
//            break;

//       case Send_Status_OK:

//           if(currentWriteType == 1)
//           {
       /*发送完成信号给用户*/
//       bytesWritten = 0;
//       writeData.clear();
//       emit SerialDataSendOK();
//           }
//           else if(currentWriteType == 2)
//           {
//               bytesWritten = 0;
//               writeACK.clear();
//               ackList.removeAt(0);
//           }
//           currentWriteType = 0;
//           sendstatus = Send_Status_Idle;
//           break;
//       case Send_Status_Error:
//#if COMMAND_ACK_CHECK_CONTROL
//           emit RS232CommunicationError();
//           writeData.clear();
//           ackList.clear();
//           currentWriteType = 0;
//           sendstatus = Send_Status_Idle;
//#endif
//           qDebug()<<__FILE__<<__FUNCTION__<<__LINE__<<"RS232 Communication Error,Please check RS232 Cable Line.";
//           break;
//   }
}




/*串口接收命令流程，按通讯协议的要求执行*/
void RS232ComProtocal::ReceivedCommandDealFlow(QByteArray data,uint8_t xorcheck)
{
    QByteArray ack;
    if(needXORCheck)
    {
        uint8_t xorvalue=0;
        if(data.size()>1)
            xorvalue = GetXorCheckValue(data.mid(1,data.size()));


        if(writeACK.size())
        {
            qDebug()<<"Still acking processing...";
        }

        if(xorvalue == xorcheck)
        {
            /*校验正确处理*/
            ack.append(ACK_OK_1);
            ack.append(ACK_OK_2);
            ack.append(ACK_OK_3);

            ackList.append(ack);

            /*接收到一帧数据，发送给用户处理*/
            emit ReceivedSerialDataOK(data);
        }
        else
        {
            /*校验错误处理*/
            ack.append(ACK_ERROR_1);
            ack.append(ACK_ERROR_2);
            ack.append(ACK_ERROR_3);

            ackList.append(ack);
        }
    }
    else
    {
        uint8_t xorvalue=0;
        if(data.size()>1)
            xorvalue = GetXorCheckValue(data.mid(1,data.size()));
        /*接收到一帧数据，发送给用户处理*/
        if(xorvalue == xorcheck)
        {
            emit ReceivedSerialDataOK(data);
        }
    }
}

/*设置当前工作模式*/
void RS232ComProtocal::SetWorkMode(WorkMode mode)
{
    workmode = mode;
    if(workmode == WorkMode_PC_TO_MAINBOARD)
    {
        if(COMMAND_CHECK_CONTROL == 0)
        {
            needXORCheck = false;
        }
        else
        {
            needXORCheck = true;
        }
    }
    else
    {
        needXORCheck = false;
    }
}

/*异或校验*/
uint8_t RS232ComProtocal::GetXorCheckValue(QByteArray data)
{
    uint8_t xorvalue = 0;

    for(int i=0; i<data.size(); i++)
    {
        xorvalue ^= (uint8_t)data.at(i);
    }

    return xorvalue;
}

/*用协议封装发送数据,data 字段不包含长度字段*/
QByteArray RS232ComProtocal::AddProtocalShell(QByteArray data)
{
    QByteArray result;
    uint8_t len_h,len_l,xorvalue;

    /*解析长度字段*/
    len_h = data.size()>>8;
    len_l = data.size()%256;

    /*增加协议头*/
    result.append(MAIN_STX1);
    result.append(MAIN_STX2);

    /*增加长度*/
    result.append(len_h);
    result.append(len_l);

    /*增加数据字段*/
    result.append(data);

    /*增加XOR Check字段*/
    if(data.size()>1)
        xorvalue = GetXorCheckValue(data.mid(1,data.size()));

    result.append(xorvalue);

    SendFlagB++;
    if(SendFlagB > 511)
        SendFlagB = 0;
    result.append(SendFlagB);
    result.append(MAIN_RTX1);

    return result;
}

/*用协议封装发送数据,data 字段不包含长度字段*/
QByteArray RS232ComProtocal::AddProtocalShellLis(QByteArray data)
{
    QByteArray result;
    uint8_t len_h,len_l;

    /*解析长度字段*/
    len_h = data.size()>>8;
    len_l = data.size()%256;

    /*增加协议头*/
    result.append(LIS_STX);

    /*增加长度*/
//    result.append(len_h);
//    result.append(len_l);

    /*增加数据字段*/
    result.append(data);

    result.append(LIS_RTX);

    return result;
}

/*去掉接收数据的协议外壳,去除后剩余Motor CMD DATA字段*/
QByteArray RS232ComProtocal::RemoveProtocalShell(QByteArray data)
{
     QByteArray result =data;

     /*去掉STX PKL字段*/
     result.remove(0,4);

     /*去掉XOR Check*/
     result.remove(result.size()-2,2);

     return result;
}


/*串口收到数据处理子流程，判断是否完成一帧数据的接收*/
void RS232ComProtocal::handleSerialDataReceived(const QByteArray &data)
{
    readDatamutex.lock();

    /*收到的数据累加到缓冲中*/
    readData.append(data);

    readDatamutex.unlock();
}

/*串口收到数据处理子流程，判断是否完成一帧数据的接收*/
void RS232ComProtocal::handleSerialDataReceivedLis(const QByteArray &data)
{
    readDatamutex.lock();

    /*收到的数据累加到缓冲中*/
    readDataLis.append(data);

    readDatamutex.unlock();
}

/*串口发送命令控制流程，按通讯协议的要求执行*/
void RS232ComProtocal::SendCommandFlowLis()
{
    if(writeDataLis.size())
    {
        bytesWrittenLis = 0;
        emit SendSerialDataLis(writeDataLis);
        emit SerialDataSendOKLis();
        writeDataLis.clear();
        QThread::msleep(10);
        sendstatusLis = Send_Status_Idle;
    }
}

/*Lis串口接收命令控制流程*/
void RS232ComProtocal::ReceiveCommandFlowLis(int &last_size,qint64 &timeout)
{
    int getstxflag=-1;
    int stx_index = readDataLis.indexOf(LIS_STX);
    int rtx_index=-1;
    if(stx_index == -1)
    {
        readDataLis.clear();
    }
    else
    {
        if(stx_index == 0)
        {
            /*接收正常不处理*/
        }
        else
        {
            readDataLis.remove(0,stx_index);
        }
        rtx_index = readDataLis.indexOf(LIS_RTX);
        if(rtx_index>0&&rtx_index>stx_index)
        {
            getstxflag = 1;
        }
    }
    if((readDataLis.size()>=3)&&(getstxflag>0))
    {
        //        uint length = (uchar)readDataLis.at(1)*256 + (uchar)readDataLis.at(2);
        //        if(length>0&&length<10000)
        //        {
        //            if((uint)readDataLis.size() >= (length + 2))
        //            {
        //                if((uchar)readDataLis.at(length+3)==LIS_RTX)
        //                {
        int length=rtx_index-stx_index;
        /*对接收到的数据进行校验判断并处理*/
        emit ReceivedSerialDataOKLis(readDataLis.mid(stx_index+1,length-1));

        /*将收到的数据截取出来*/
        readDataLis.remove(stx_index,length+1);
        //                }
        //                else
        //                {
        //                    readDataLis.remove(0,1);
        //                }
        //            }
        //        }
        //        else
        //        {
        //            readDataLis.remove(0,1);
        //        }
    }
    if(last_size)
    {
        timeout++;
        if(timeout >= WAIT_COMPLETE_FRAME_TIMEOUT)
        {
            if(readDataLis.size() == last_size)
            {
                readDataLis.clear();
                timeout = 0;
            }
        }
    }
    else
    {
        timeout = 0;
    }

    last_size = readDataLis.size();
}

/*串口已经发送数据处理子流程，判断是否完成一帧数据的发送*/
void RS232ComProtocal::handleSerialDataWritten(qint64 bytes)
{
    writtenBytesmutex.lock();

    bytesWritten+= bytes;

    if(currentWriteType == 2)
    {
        qDebug()<<writeACK.toHex();
        if(bytesWritten == writeACK.size())
        {
            sendstatus = Send_Status_OK;
        }
    }
    else
    {

        if(bytesWritten == writeData.size())
        {
            /*完成串口数据发送，设置相关标识*/
            if(needXORCheck)
            {
               /*进入等待对方应答流程*/
               if(sendstatus == Send_Status_Sending)
               {
                    sendstatus = Send_Status_Waiting_ACK;
                    /*clear timer index to 0,等待应答超时计数器清零*/
#if COMMAND_ACK_CHECK_CONTROL

                    ackTimeoutCount = 0;

#endif

               }
            }
            else
            {
               sendstatus = Send_Status_OK;
            }
        }
    }
    sendstatus = Send_Status_OK;

    writtenBytesmutex.unlock();
}

void RS232ComProtocal::handleUserCommandSendLis(const QByteArray &data)
{
    if(sendstatusLis == Send_Status_Idle)
    {
        QByteArray newdata;

        newdata = AddProtocalShellLis(data);

        writeDataLis.clear();
        writeDataLis = newdata;
    }
}

/*从用户接收用户数据发送信号的处理*/
void RS232ComProtocal::handleUserCommandSend(const QByteArray &data)
{
    if(sendstatus == Send_Status_Idle)
    {
        SendCommand(data);
    }
}


#if COMMAND_ACK_CHECK_CONTROL

/*定时器实时时间到事件处理*/
void RS232ComProtocal::ackTimerUpdate()
{
    ackTimeoutCount++;
}

#endif



