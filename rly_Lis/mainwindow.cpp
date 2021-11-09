#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tools/RS232Com/RS232ComProtocal.hpp"
#include "Tools/RS232Com/RS232ComThread.hpp"
#include "Tools/RS232Com/RS232ComThreadLis.hpp"
#include "Tools/RS232Com/RS232ComUserDeal.hpp"
#include "Tools/Sqlite/sqlitedriver.hpp"
#include "Tools/TCPCom/communicationTcp.h"
#include "Tools/Configer/confighelper.hpp"
#include "diaedittestshow.h"
#include "sqlhelper.h"
#include "diatestmanager.h"
#include "diasampleno.h"

#include <QHostInfo>
#include <QMessageBox>
#include <QCheckBox>
#include <QDebug>
#include <QRegExp>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_db = sqlhelper::getSingleton();
    // 创建一个日志文件，5MB，最多 3 个。
    m_rotating_logger = spdlog::rotating_logger_mt("实验数据", "logs/SendAndRecive.txt", 1048576 * 5, 3);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::slot_btn_SerialOpen_clicked
 * 打开/关闭串口连接功能
 */
void MainWindow::slot_btn_SerialOpen_clicked()
{
    if(ui->pushButton_SerialOpen->text() == "打开串口") {
        RS232ThreadLis->serial->setPortName(ui->comboBox_com->currentText());
        RS232ThreadLis->serial->setBaudRate(ui->comboBox_rate->currentText().toInt());
        RS232ThreadLis->serial->setDataBits(QSerialPort::Data8); // 8字节
        RS232ThreadLis->serial->setParity(QSerialPort::NoParity); //不校验奇偶位，异常由协议检查判断
        RS232ThreadLis->serial->setStopBits(QSerialPort::OneStop); // 1停止位
        RS232ThreadLis->serial->setFlowControl(QSerialPort::NoFlowControl); // 无流控制
        if(RS232ThreadLis->RS232ComOpen()) {
            ui->pushButton_SerialOpen->setText("关闭串口");
            // 串口功能开启时不能更改串口和码率
            ui->comboBox_com->setEnabled(false);
            ui->comboBox_rate->setEnabled(false);
        }
    } else {
        RS232ThreadLis->RS232ComClose();
        ui->pushButton_SerialOpen->setText("打开串口");

        ui->comboBox_com->setEnabled(true);
        ui->comboBox_rate->setEnabled(true);
    }
}

/**
 * @brief MainWindow::slot_btn_Listen_clicked
 * 打开/关闭监听功能
 */
void MainWindow::slot_btn_Listen_clicked()
{
    if("监听" == ui->pushButton_Listen->text()) {
        QString ip = ui->comboBox_IP->currentText();
        QString port = ui->lineEdit_sPort->text();
        if(ip.isEmpty() || port.isEmpty()) {
            QMessageBox::warning(this,"警告","IP地址或端口号不能为空!");
            return;
        }
        emit signalOpenTcp(ip, port, 0);
        ui->pushButton_Listen->setText("停止");
        ui->comboBox_IP->setEnabled(false);
        ui->lineEdit_sPort->setEnabled(false);
    } else {
        emit signalCloseTcp();
        ui->pushButton_Listen->setText("监听");
        ui->comboBox_IP->setEnabled(true);
        ui->lineEdit_sPort->setEnabled(true);
    }
}

/**
 * @brief MainWindow::slot_btn_AddTest_clicked
 * 添加一个新的测试项目 PT、FIB...等
 */
void MainWindow::slot_btn_AddTest_clicked()
{
    QVector<QPair<QString, QString>> allParas;
    int cols = ui->tableWidget_Test->columnCount();
    for(int col = 2; col < cols; col++)
    {
        QPair<QString, QString> pair;
        pair.first = ui->tableWidget_Test->horizontalHeaderItem(col)->text();
        pair.second = "0";
        allParas.push_back(pair);
    }
    diaTestManager diatestmanager(allParas);
    diatestmanager.setWindowTitle("添加项目");
    if(diatestmanager.exec() == QDialog::Accepted)
    {
        UpdataTestData();
    }
}

/**
 * @brief MainWindow::slot_btn_DeleteTest_clicked
 * 删除一个项目，默认的项目无法进行删除。
 */
void MainWindow::slot_btn_DeleteTest_clicked()
{
    if(!ui->tableWidget_Test->currentItem() || ui->tableWidget_Test->currentItem()->row() < 7)
    {
        QMessageBox::information(this, "提示", "未选中项目/默认项目不能删除！");
        return;
    }

    QString strQuestion = QString("是否删除项目 %1 ?").arg(ui->tableWidget_Test->item(ui->tableWidget_Test->currentItem()->row(), 0)->text());
    if (QMessageBox::No == QMessageBox::question(this, "提问", strQuestion))
    {
        return;
    }

    int row = ui->tableWidget_Test->currentRow();
    QString strSqlWhere = QString("where item_name = '%1' and item_code = '%2'")
            .arg(ui->tableWidget_Test->item(row, 0)->text())
            .arg(ui->tableWidget_Test->item(row, 1)->text());

    if(0 != m_db->delData("item_parameter", strSqlWhere))
    {
        return;
    }
    UpdataTestData();
    //删除成功后，清空样本数据
    m_SampleData.clear();
    m_strCurrentSampleNo.clear();
    auto rows = ui->tableWidget_sampleNo->rowCount(); // ui->tableWidget_sampleNo->clearContents() 不能清除Item；
    for(int row = 0; row < rows; row++)
    {
        ui->tableWidget_sampleNo->removeRow(row);
    }
}

/**
 * @brief MainWindow::slot_btn_SendTest_clicked
 * 将样本号及实验数据下发
 */
void MainWindow::slot_btn_SendTest_clicked()
{
    SendCommendData();
}

/**
 * @brief MainWindow::slot_btn_Edit_clicked
 * 打开编辑项目参数界面
 */
void MainWindow::slot_btn_Edit_clicked()
{
    DiaEditTestShow diaedittestshow;
    if(diaedittestshow.exec() == QDialog::Accepted)
    {
        UpdataTestData();
    }
}

/**
 * @brief MainWindow::slot_btn_ClearTestResult_clicked
 * 清空测试结果列表
 */
void MainWindow::slot_btn_ClearTestResult_clicked()
{
    if (QMessageBox::No == QMessageBox::question(this, "提问", "是否清空实验结果？"))
    {
        return;
    }

    auto rows = ui->tableWidget_result->rowCount();
    while(rows >= 0)
    {
        ui->tableWidget_result->removeRow(rows--);
    }
}

/**
 * @brief MainWindow::slot_btn_AddSample_clicked
 * 打开添加样本号界面
 */
void MainWindow::slot_btn_AddSample_clicked()
{
    DiaSampleNo diasampleno;
    if(diasampleno.exec() == QDialog::Accepted)
    {
        QString strSampleNo;
        diasampleno.getSampleNo(strSampleNo);

        if(strSampleNo.isEmpty())
        {
            QMessageBox::warning(this, "警告", "样本号不能为空!");
            return;
        }
        if(m_SampleData.contains(strSampleNo))
        {
            QMessageBox::warning(this, "警告", "该样本号已添加!");
            return;
        }

        int row = ui->tableWidget_sampleNo->rowCount();
        ui->tableWidget_sampleNo->insertRow(row);
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(strSampleNo);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_sampleNo->setItem(row, 0, item);

        QSet<QString> sReagents;
        m_SampleData.insert(strSampleNo, sReagents);

        ui->tableWidget_sampleNo->setCurrentCell(row, 0);
        m_strCurrentSampleNo = strSampleNo;
    }
}

/**
 * @brief MainWindow::slot_btn_DeleteSample_clicked
 * 删除一个选中的标本号
 */
void MainWindow::slot_btn_DeleteSample_clicked()
{
    if(!ui->tableWidget_sampleNo->currentItem())
    {
        QMessageBox::warning(this, "警告", "未选中任何样本号!");
        return;
    }
    int row = ui->tableWidget_sampleNo->currentRow();
    QString strSampleNo = ui->tableWidget_sampleNo->item(row, 0)->text();
    QString strQuestion = QString("是否删除样本号 %1!").arg(strSampleNo);
    if(QMessageBox::Yes != QMessageBox::question(this, "警告", strQuestion))
    {
        return;
    }
    m_SampleData.remove(strSampleNo);
    ui->tableWidget_sampleNo->removeRow(row);
    // 将当前样本号置空
    m_strCurrentSampleNo = "";
}

/**
 * @brief MainWindow::slot_tableWidget_Test_cellDoubleClicked
 * @param row
 * @param column
 * 双击打开项目参数编辑界面，可以修改项目参数。
 */
void MainWindow::slot_tableWidget_Test_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    QVector<QPair<QString, QString>> allParas;
    int cols = ui->tableWidget_Test->columnCount();
    for(int col = 2; col < cols; col++)
    {
        QPair<QString, QString> pair;
        pair.first = ui->tableWidget_Test->horizontalHeaderItem(col)->text();
        pair.second = ui->tableWidget_Test->item(row, col)->text();
        allParas.push_back(pair);
    }
    QString strName = ui->tableWidget_Test->item(row, 0)->text();
    QString strCode = ui->tableWidget_Test->item(row, 1)->text();
    diaTestManager diatestmanager(allParas, strName, strCode);
    diatestmanager.setWindowTitle("修改项目");
    if(diatestmanager.exec() == QDialog::Accepted)
    {
        UpdataTestData();
    }
}

/**
 * @brief MainWindow::slot_tableWidget_Test_cellClicked
 * @param row
 * @param column
 * 点击某行Item，选中该行，改变第一列的CheckBox选中状态
 */
void MainWindow::slot_tableWidget_Test_cellClicked(int row, int column)
{
    Q_UNUSED(column);
    if(m_strCurrentSampleNo.isEmpty())
    {
        return;
    }

    auto check = ui->tableWidget_Test->item(row, 0);
    if(check->checkState() == Qt::Checked)
    {
        check->setCheckState(Qt::Unchecked);
        auto strReagent = ui->tableWidget_Test->item(row, 1)->text();
        m_SampleData[m_strCurrentSampleNo].remove(strReagent);
    }
    else
    {
        check->setCheckState(Qt::Checked);
        auto strReagent = ui->tableWidget_Test->item(row, 1)->text();
        m_SampleData[m_strCurrentSampleNo].insert(strReagent);
    }
}

/**
 * @brief MainWindow::slot_tableWidget_sampleNo_currentCellChanged
 * 响应样本号的切换，刷新测试项目表格的各项目选中状态。
 */
void MainWindow::slot_tableWidget_sampleNo_currentCellChanged(int, int, int, int)
{
    if(!ui->tableWidget_sampleNo->currentItem())
    {
        return;
    }

    m_strCurrentSampleNo = ui->tableWidget_sampleNo->currentItem()->text();

    int rows = ui->tableWidget_Test->rowCount();
    for(int row = 0; row < rows; row++)
    {
        auto itemName = ui->tableWidget_Test->item(row, 0);
        auto itemCode = ui->tableWidget_Test->item(row, 1);
        if(m_SampleData[m_strCurrentSampleNo].contains(itemCode->text()))
        {
            itemName->setCheckState(Qt::Checked);
        }
        else
        {
            itemName->setCheckState(Qt::Unchecked);
        }
    }
}

void MainWindow::slot_logTimer()
{
    connect(m_timer, &QTimer::timeout,[=]()
    {
        m_rotating_logger->flush();
    });
}

void MainWindow::Init()
{
    setWindowTitle("LIS工具");
    /// 初始化串口数据 及 TCP数据
    QString path_comini = "./config.ini";
    RS232Thread = new RS232ComThread(path_comini);//("config.ini"); // 没有config配置文件
    RS232Protocal = new RS232ComProtocal(this);
    RS232User = new RS232ComUserDeal(this);
    RS232ThreadLis=new RS232ComThreadLis(path_comini);

    QStringList slComs, slComIps;
    GetCommInfor(slComs, slComIps);
    ui->comboBox_com->addItems(slComs);
    ui->comboBox_IP->addItems(slComIps);
    QRegExp rx("[0-9]{5}");
    ui->lineEdit_sPort->setValidator(new QRegExpValidator(rx, this));

    tcpListen = new CommunicationTcp;
    connect(this,SIGNAL(signalOpenTcp(QString,QString,int)),tcpListen,SLOT(slotOpenTcp(QString,QString,int)));
    connect(this,SIGNAL(signalCloseTcp()),tcpListen,SLOT(closeTcp()));
    connect(this, SIGNAL(signalSendPcData(QByteArray)), tcpListen,SLOT(slotTcpWrite(QByteArray)),Qt::QueuedConnection);
    connect(tcpListen,SIGNAL(tcpReceived(QByteArray)),this,SLOT(slot_LisReceive_Paser(QByteArray)));
    connect(RS232Protocal,&RS232ComProtocal::SendSerialData,RS232Thread,&RS232ComThread::handleSendSerialData);
    /*串口类发送已经完成发送的信号到协议模块*/
    connect(RS232Thread,&RS232ComThread::RS232BytesWritten,RS232Protocal,&RS232ComProtocal::handleSerialDataWritten);
    /*串口类发送新收到数据的信号到协议模块*/
    connect(RS232Thread,&RS232ComThread::RS232ReadyRead,RS232Protocal,&RS232ComProtocal::handleSerialDataReceived);
    /*用户模块 <---------->协议模块*/
    /*用户模块通过协议模块发送数据*/
    connect(RS232User,&RS232ComUserDeal::SendUserData,RS232Protocal,&RS232ComProtocal::handleUserCommandSend);
    /*协议模块发送已经完成命令发送的信号到用户模块*/
    connect(RS232Protocal,&RS232ComProtocal::SerialDataSendOK,RS232User,&RS232ComUserDeal::handleSerialDataSendOK);
    /*协议模块发送新收到的数据到用户模块*/
    connect(RS232Protocal,&RS232ComProtocal::ReceivedSerialDataOK,RS232User,&RS232ComUserDeal::handleReceivedSerialDataOK);
    connect(RS232Protocal,&RS232ComProtocal::SendSerialDataLis,RS232ThreadLis,&RS232ComThreadLis::handleSendSerialData);
    /*串口类发送新收到数据的信号到协议模块*/
    connect(RS232ThreadLis,&RS232ComThreadLis::RS232ReadyRead,RS232Protocal,&RS232ComProtocal::handleSerialDataReceivedLis);
    /*用户模块 <---------->协议模块*/
    /*用户模块通过协议模块发送数据*/
    connect(RS232User,&RS232ComUserDeal::SendUserDataLis,RS232Protocal,&RS232ComProtocal::handleUserCommandSendLis);
    /*协议模块发送已经完成命令发送的信号到用户模块*/
    connect(RS232Protocal,&RS232ComProtocal::SerialDataSendOKLis,RS232User,&RS232ComUserDeal::handleSerialDataSendOKLis);
    /*协议模块发送新收到的数据到用户模块*/
    connect(RS232Protocal,&RS232ComProtocal::ReceivedSerialDataOKLis,RS232User,&RS232ComUserDeal::handleReceivedSerialDataOKLis);
    connect(RS232User,&RS232ComUserDeal::SendReceivedDataLis,this,&MainWindow::slot_LisReceive_Paser);

    /// 初始化界面
    // 初始化结果列表
    ui->tableWidget_result->setColumnCount(4);
    ui->tableWidget_result->verticalHeader()->setVisible(false);
    ui->tableWidget_result->setAlternatingRowColors(true);
    ui->tableWidget_result->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    ui->tableWidget_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_result->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_result->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_result->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList header;
    header<<"样本号"<<"项目名称"<<"结果值"<<"报告时间";
    ui->tableWidget_result->setHorizontalHeaderLabels(header);
    for(int i=0;i<ui->tableWidget_result->columnCount();i++)
    {
        ui->tableWidget_result->setColumnWidth(i,ui->tableWidget_result->width()/4);
    }

    // 初始化样本列表
    ui->tableWidget_sampleNo->setColumnCount(1);
    header.clear();
    header<<"样本号";
    ui->tableWidget_sampleNo->setHorizontalHeaderLabels(header);
    ui->tableWidget_sampleNo->verticalHeader()->setVisible(false);
    ui->tableWidget_sampleNo->setAlternatingRowColors(true);
    ui->tableWidget_sampleNo->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    ui->tableWidget_sampleNo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_sampleNo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_sampleNo->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_sampleNo->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget_sampleNo->horizontalHeader()->setStretchLastSection(true);

    // 初始化项目列表
    ui->tableWidget_Test->setColumnCount(header.size());
    ui->tableWidget_Test->setHorizontalHeaderLabels(header);
    ui->tableWidget_Test->verticalHeader()->setVisible(false);
    ui->tableWidget_Test->setAlternatingRowColors(true);
    ui->tableWidget_Test->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    ui->tableWidget_Test->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Test->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Test->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Test->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget_Test->horizontalHeader()->resizeSections(QHeaderView::Stretch);
    ui->tableWidget_Test->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    UpdataTestData();

    m_timer = new QTimer(this);
    slot_logTimer();
    m_timer->start(10000);
}
/**
 * @brief MainWindow::GetCommInfor
 * 获取当前PC的串口及IP地址
 * @param slcoms OUT 串口
 * @param slComIp OUT IP地址
 */
void MainWindow::GetCommInfor(QStringList &slcoms, QStringList &slComIp)
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString com =  info.portName();
        slcoms.append(com);
    }

    auto localHostName = QHostInfo::localHostName();
    auto info = QHostInfo::fromName(localHostName);
    foreach(auto address, info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            slComIp.append(address.toString());
    }
}

/**
 * @brief MainWindow::slot_LisReceive_Paser
 * 回复心跳，处理LIS传入的结果数据。
 * @param data IN LIS传入的数据
 */
void MainWindow::slot_LisReceive_Paser(QByteArray data)
{
    if((data.size()>2) && (data.at(0)==0x02) && (data.at(data.size()-1)==0x03))
    {
        data.remove(data.size()-1,1);
        data.remove(0,1);
    }
    //回复心跳
    if(data.at(0)=='A')
    {
        QByteArray command;
        command.append("AAAAA");
        SendData(command);
    }
    if(data.at(0)=='B')
    {
        data.insert(0,0x02);
        data.insert(data.size(),0x03);
        while(data.size()>=18)
        {
            if(data.at(0)==0x02&&data.at(1)=='B'&&data.at(17)==0x03)
            {
                QString strSampleID = data.mid(2,15).trimmed();
                if(!strSampleID.isEmpty() && strSampleID!="?" && strSampleID != "NO")
                {
                    m_SampleData.insert(strSampleID, QSet<QString>());
                }
                data.remove(0,18);
            }
            else
            {
                data.remove(0,1);
            }
        }
        UpdateSamples();
        SendCommendData();
    }
    else if(data.at(0)=='D')
    {
        m_rotating_logger->info("结果数据 {}", data);

        int offset=0;
        offset+=9;

        //年月日时分
        QString strDataTime = data.mid(offset,10).trimmed();
        QString strTime = strDataTime.mid(0,2)+"-"+strDataTime.mid(2,2)+"-"+
                strDataTime.mid(4,2)+" "+strDataTime.mid(6,2)+":"+strDataTime.mid(8,2);

        offset+=16;
        //        QString strSampleHole = data.mid(offset,2).trimmed();   //样本孔位号 没有使用
        offset+=2;
        QString strSampleID = data.mid(offset,15).trimmed();    //样本Id
        offset+=16;
        offset+=15;

        //数据字段
        QString strRemain = data.mid(offset);

        QList<QHash<QString, QString>> item_info;
        m_db->getItemData(item_info);
        for (int t=0; t<strRemain.size()/9; t++)
        {
            auto row = ui->tableWidget_result->rowCount();
            ui->tableWidget_result->insertRow(row);
            ui->tableWidget_result->setItem(row,0,new QTableWidgetItem(strSampleID,Qt::AlignHCenter));
            ui->tableWidget_result->setItem(row,3,new QTableWidgetItem(strTime,Qt::AlignHCenter));

            QString item_code = strRemain.mid(t*9,2).append("0");  //项目编号
            QString item_type = strRemain.mid(t*9+2,1);            //项目类型
            QString item_data = strRemain.mid(t*9+3,5);
            QString item_sign = strRemain.mid(t*9+8,1);

            //            qDebug()<<item_code<<item_type<<item_data<<item_sign;
            // 根据协议配置文件 获取item_type对应的字段，如 2 对应 浓度小数点 3 对应 R 小数点等
            QString itemName;
            int point = 0;
            item_type.append("_Protocol");
            QString colName = configHelper::readInit("Name", item_type);
            for(auto hash: item_info)
            {
                if(hash["item_code"] == item_code)
                {
                    itemName = hash["item_name"];
                    point = hash[colName].toInt();
                    break;
                }
            }
            QString suffix = configHelper::readInit("Suffix", item_type);
            if(!suffix.isEmpty())
            {
                itemName.append(QString(" " + suffix));
            }
            ui->tableWidget_result->setItem(row,1,new QTableWidgetItem(itemName,Qt::AlignHCenter));

            if(item_data == "*****")
            {
                item_data = "****";
            }
            else
            {
                if(item_data.contains("*"))
                {
                    item_data.remove("*");
                    double result_dbl=item_data.toInt();
                    result_dbl=result_dbl*qPow(10,-point);
                    item_data=QString::number(result_dbl,'f',point);
                    item_data = "*"+item_data;
                }
                else
                {
                    double result_dbl=item_data.toInt();
                    result_dbl=result_dbl*qPow(10,-point);
                    item_data=QString::number(result_dbl,'f',point);
                }
            }
            ui->tableWidget_result->setItem(row,2,new QTableWidgetItem(item_data,Qt::AlignHCenter));
        }
    }
}

/**
 * @brief MainWindow::UpdataTestData
 * 更新项目测试列表
 */
void MainWindow::UpdataTestData()
{
    ui->tableWidget_Test->clear();

    QStringList slHeaders;
    m_db->getItemHeaders(slHeaders);
    ui->tableWidget_Test->setColumnCount(slHeaders.size());
    ui->tableWidget_Test->setHorizontalHeaderLabels(slHeaders);

    QList<QHash<QString, QString>> lhsItemInfo;
    m_db->getItemData(lhsItemInfo);
    int cols = lhsItemInfo.first().size();
    int rows = lhsItemInfo.size();
    ui->tableWidget_Test->setRowCount(rows);

    for(int row = 0; row < rows; row++)
    {
        QTableWidgetItem *item0 = new QTableWidgetItem();
        item0->setText(lhsItemInfo.at(row)["item_name"]);
        item0->setCheckState(Qt::Unchecked);
        item0->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_Test->setItem( row, 0, item0);

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(lhsItemInfo.at(row)["item_code"]);
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_Test->setItem( row, 1, item1);

        for(int col = 2; col < cols; col++)
        {
            QTableWidgetItem *item2 = new QTableWidgetItem();
            item2->setText(lhsItemInfo.at(row)[slHeaders.at(col)]);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_Test->setItem( row, col, item2);
        }
    }
    // 隐藏未开启的列
    QList<QHash<QString, QString>> lhsParas;
    m_db->getAllParameters(lhsParas);
    for(auto hash: lhsParas)
    {
        int cols = ui->tableWidget_Test->columnCount();
        for(int col = 0; col < cols; col++)
        {
            if(hash["parameter"] == ui->tableWidget_Test->horizontalHeaderItem(col)->text())
            {
                if("0" == hash["isOpen"])
                    // 删除改列会导致莫名其妙的问题，故改为隐藏。
                    ui->tableWidget_Test->hideColumn(col);
                else
                    ui->tableWidget_Test->showColumn(col);
            }
        }
    }
}
/**
 * @brief MainWindow::UpdateSamples
 * 更新样本号列表
 */
void MainWindow::UpdateSamples()
{
    ui->tableWidget_sampleNo->clear();
    int rows = m_SampleData.size();
    ui->tableWidget_sampleNo->setRowCount(rows);
    int row = 0;
    for(auto strKey: m_SampleData.keys())
    {
        auto item = new QTableWidgetItem();
        item->setText(strKey);
        ui->tableWidget_sampleNo->setItem(row++, 0, item);
    }
}
/**
 * @brief MainWindow::SendCommendData
 * 发送样本数据
 */
void MainWindow::SendCommendData()
{
    if(m_SampleData.empty())
    {
        QMessageBox::warning(this,"警告","样本号未设置！");
        return;
    }

    for(auto strkey: m_SampleData.keys())
    {
        QByteArray command;
        command.append("B");
        QString strSampleId = strkey;
        while(strSampleId.length()<15)
            strSampleId.insert(0, ' ');
        command.append(strSampleId);

        for(auto strCode: m_SampleData[strkey])
        {
            while(strCode.length()<9)
                strCode.append(" ");
            command.append(strCode);
        }
        SendData(command);
        m_rotating_logger->info("实验下发数据 {}", command);
    }
    QMessageBox::information(this,"提示","实验下发成功！");
}
/**
 * @brief MainWindow::SendData
 * @param command
 * 分别发送TCP和串口数据。
 */
void MainWindow::SendData(QByteArray &command)
{
    RS232User->AddSendCommandLis(command);
    /// ！！TCP 需要前后加上 0x02 0x03
    command.insert(0, 0x02).append(0x03);
    emit signalSendPcData(command);
}
