/*------------------------------串口通讯模块底层读写控制接口实现代码--------------------------------*/
#include <QCoreApplication>
#include "Tools/RS232Com/RS232ComThread.hpp"
#include <QtDebug>
#include <QMessageBox>
#include <QSettings>



/*串口同构体,传递串口配置文件路径*/
RS232ComThread::RS232ComThread(QString configfile,QObject *parent) : QObject(parent)
{
    /*实例化串口对象*/
    serial = new QSerialPort();

    /*配置文件名称赋值*/
    ConfigFile = configfile;

    /*从配置文件获取串口配置参数*/
    UpdateComConfig(configfile);

    /*已经完成串口数据发送处理*/
    //connect(serial, &QSerialPort::bytesWritten, this, &handleBytesWritten);

    /*已经完成串口数据接收处理*/
    connect(serial, &QSerialPort::readyRead, this, &handleReadyRead);
}

/*串口配置文件*/
int RS232ComThread::UpdateComConfig(QString configfile)
{
    /*读取串口的配置文件*/
    QSettings portsetting(configfile,QSettings::IniFormat);

    /*获取串口名*/
    setting.name = portsetting.value("RS232/name","COM1").toString();

    /*获取串口波特率*/
    setting.baudRate = portsetting.value("RS232/baudRate",9600).toInt();

    /*获取串口数据位*/
    setting.stringDataBits = portsetting.value("RS232/dataBits","Data8").toString();
    if(setting.stringDataBits == "Data5")
    {
        setting.dataBits = QSerialPort::Data5;
    }
    else if(setting.stringDataBits == "Data6")
    {
        setting.dataBits = QSerialPort::Data6;
    }
    else if(setting.stringDataBits == "Data7")
    {
        setting.dataBits = QSerialPort::Data7;
    }
    else if(setting.stringDataBits == "Data8")
    {
        setting.dataBits = QSerialPort::Data8;
    }

    /*获取串口奇偶校验位*/
    setting.stringParity = portsetting.value("RS232/parity","NoParity").toString();

    if(setting.stringParity == "NoParity")
    {
        setting.parity = QSerialPort::NoParity;
    }
    else if(setting.stringParity == "EvenParity")
    {
        setting.parity = QSerialPort::EvenParity;
    }
    else if(setting.stringParity == "OddParity")
    {
        setting.parity = QSerialPort::OddParity;
    }
    else if(setting.stringParity == "SpaceParity")
    {
        setting.parity = QSerialPort::SpaceParity;
    }
    else if(setting.stringParity == "MarkParity")
    {
        setting.parity = QSerialPort::MarkParity;
    }

    /*获取串口停止位*/
    setting.stringStopBits = portsetting.value("RS232/stopBits","OneStop").toString();

    if(setting.stringStopBits == "OneStop")
    {
        setting.stopBits = QSerialPort::OneStop;
    }
    else if(setting.stringStopBits == "OneAndHalfStop")
    {
        setting.stopBits = QSerialPort::OneAndHalfStop;
    }
    else if(setting.stringStopBits == "TwoStop")
    {
        setting.stopBits = QSerialPort::TwoStop;
    }

    /*获取串口控制流*/
    setting.stringFlowControl = portsetting.value("RS232/flowControl","NoFlowControl").toString();

    if(setting.stringFlowControl == "NoFlowControl")
    {
        setting.flowControl = QSerialPort::NoFlowControl;
    }
    else if(setting.stringFlowControl == "HardwareControl")
    {
        setting.flowControl = QSerialPort::HardwareControl;
    }
    else if(setting.stringFlowControl == "SoftwareControl")
    {
        setting.flowControl = QSerialPort::SoftwareControl;
    }

    /*配置串口参数*/
    serial->setPortName(setting.name);
    serial->setBaudRate(setting.baudRate);
    serial->setDataBits(setting.dataBits);
    serial->setParity(setting.parity);
    serial->setStopBits(setting.stopBits);
    serial->setFlowControl(setting.flowControl);
    return 1;
}

/*串口开启*/
int RS232ComThread::RS232ComOpen()
{
    if (serial->isOpen())
        serial->close();

    if (serial->open(QIODevice::ReadWrite))
    {
        return 1;
    }
    else
    {
        QMessageBox::critical(NULL,"错误", "RS232 Open Error! "+serial->errorString(),QMessageBox::Yes);
    }
    return 0;
}

/*串口关闭*/
void RS232ComThread::RS232ComClose()
{
    if (serial->isOpen())
    {
        serial->close();
    }
}

/*获取串口列表*/
QStringList RS232ComThread::GetCommInfor()
{
    QStringList comlist;
    comlist.clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString com =  info.portName();
        comlist.append(com);
    }

    return comlist;
}

QString RS232ComThread::ByteArrayToHexString(QByteArray data)
{
    QString ret(data.toHex().toUpper());
    int len = ret.length()/2;
    for(int i=1;i<len;i++)
    {
        ret.insert(2*i+i-1," ");
    }
    return ret;
}

/*串口数据发送接口*/
int RS232ComThread::RS232ComWrite(QByteArray array)
{
    if (serial->isOpen())
    {
        QString senddata="serial send:"+ByteArrayToHexString(array);
        serial->write(array);
        return 1;
    }
    else
    {
        return 0;
    }

}

/*串口数据读取接口*/
QByteArray RS232ComThread::RS232ComRead()
{
    QByteArray data;
    if (serial->isOpen())
    {
        data =  serial->readAll();
        QString readdata="serial read:"+ByteArrayToHexString(data);
    }

    return data;

}



/*通过配置文件读取串口名称*/
QString RS232ComThread::GetRS232Name()
{
     QString name;

    /*读取串口的配置文件*/
    if(ConfigFile != "")
    {
        QSettings portsetting(ConfigFile,QSettings::IniFormat);

        /*获取串口名*/
        name = portsetting.value("RS232/name","COM1").toString();
    }

    return name;

}

/*重新设置串口名称并更新到配置文件中*/
int RS232ComThread::SetRS232Name(QString name)
{
    /*读取串口的配置文件*/
    if(ConfigFile != "")
    {
        QSettings portsetting(ConfigFile,QSettings::IniFormat);

        /*设置串口名*/
        portsetting.beginGroup("RS232");
        portsetting.setValue("name",name);
        portsetting.endGroup();

        return 1;
    }
    else
    {
        return 0;
    }
}


/*和已经读取到的数据信号相关联*/
void RS232ComThread::handleReadyRead()
{
     QByteArray data = RS232ComRead();

     emit RS232ReadyRead(data);
}



/*和已经发送完成的数据信号相关联*/
void RS232ComThread::handleBytesWritten(qint64 bytes)
{
    emit RS232BytesWritten(bytes);

}

 /*其他位置调用的写接口信号槽*/
void RS232ComThread::handleSendSerialData(const QByteArray &data)
{
    RS232ComWrite(data);
}


void RS232ComThread::setSerialPort(QString com)
{
    if(com.isEmpty())
        return;
    RS232ComClose();
    SetRS232Name(com);
    UpdateComConfig(ConfigFile);
    if(RS232ComOpen())
    {
        //QMessageBox::information( "提示", "串口设置成功!",QMessageBox::Yes);
    }
    else
    {
        QMessageBox::critical(NULL,"错误", "串口设置失败!",QMessageBox::Yes);
    }
}
