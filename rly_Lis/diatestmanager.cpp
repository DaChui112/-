#include "diatestmanager.h"
#include "ui_diatestmanager.h"
#include "sqlhelper.h"
#include "Tools/Configer/confighelper.hpp"
#include <QComboBox>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>

diaTestManager::diaTestManager(QVector<QPair<QString, QString> > allParas, QString strName, QString strCode, QWidget *parent)
    :QDialog(parent),
      m_strName(strName),
      m_strCode(strCode),
      m_allParas(allParas),
      ui(new Ui::diaTestManager)
{
    ui->setupUi(this);
    m_db = sqlhelper::getSingleton();
    ui->lineEdit_Name->setText(strName);
    ui->lineEdit_Code->setText(strCode);
    QRegExp rx("[0-9]{3}");
    ui->lineEdit_Code->setValidator(new QRegExpValidator(rx, this));

    Init();
    InitData();
}

diaTestManager::~diaTestManager()
{
    delete ui;
}

/**
 * @brief diaTestManager::slot_pushButton_Apply_clicked
 * 应用槽函数。将数据添加或更新到数据库
 */
void diaTestManager::slot_pushButton_Apply_clicked()
{
    QHash<QString, QString> hsParas;
    getComboxData(hsParas);

    if("添加项目" == this->windowTitle())
    {
        m_db->addData("item_parameter", hsParas);
    }
    else if("修改项目" == this->windowTitle())
    {
        auto strSqlWhere = ui->lineEdit_Name->text();
        QString sqlWhere = QString("where item_code = '%1'")
                .arg(m_strCode);
        m_db->updateData("item_parameter", hsParas, sqlWhere);
    }
    this->accept();
}

/**
 * @brief diaTestManager::slot_pushButton_Cancel_clicked
 * 关闭窗口并取消设置。
 */
void diaTestManager::slot_pushButton_Cancel_clicked()
{
    this->close();
}

void diaTestManager::Init()
{
    m_ft1.setFamily("微软雅黑");
    m_ft1.setWeight(20);
    // 初始化表格
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    ui->tableWidget->setColumnCount(2);
    QStringList slHeaders;
    slHeaders << "参数" << "值";
    ui->tableWidget->setHorizontalHeaderLabels(slHeaders);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->horizontalHeader()->resizeSections(QHeaderView::QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

void diaTestManager::InitData()
{
    int size = m_allParas.size();
    QStringList slCombobox;
    slCombobox << "0" << "1" << "2" << "3" << "4" << "5";
    for(int row = 0; row < size; row++)
    {
        ui->tableWidget->insertRow(row);

        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(m_allParas[row].first);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 0, item);

        QComboBox *pCombobox = new QComboBox(this);
        pCombobox->setFont(m_ft1);
        pCombobox->addItems(slCombobox);
        pCombobox->setCurrentText(m_allParas[row].second);
        QWidget *w = new QWidget(this);                    //创建一个widget
        QHBoxLayout *hLayout = new QHBoxLayout();          //创建布局
        hLayout->addWidget(pCombobox);                     //添加checkbox
        hLayout->setMargin(0);                             //设置边缘距离 否则会很难看
        w->setLayout(hLayout);
        ui->tableWidget->setCellWidget(row, 1, w);

        m_data[m_allParas[row].first] = pCombobox;
    }
}

/**
 * @brief diaTestManager::getComboxData
 * @param hsParas OUT
 * 获取当前项目的所有参数数据
 */
void diaTestManager::getComboxData(QHash<QString, QString> &hsParas)
{
    // 特殊判断
    if(ui->lineEdit_Name->text().isEmpty() && ui->lineEdit_Code->text().isEmpty())
    {
        QMessageBox::warning(this, "警告", "项目名称、代号不能为空！");
        return;
    }
    hsParas["item_name"] = ui->lineEdit_Name->text();
    hsParas["item_code"] = ui->lineEdit_Code->text();
    int rows = ui->tableWidget->rowCount();
    for(int row = 0; row < rows; row++)
    {
        QString strPara = ui->tableWidget->item(row, 0)->text();
        auto cb = m_data[strPara];
        hsParas[strPara] = cb->currentText();
    }
}

/**
 * @brief diaTestManager::getAllPorotocol
 * @param sNumber
 * 获取配置文件信息，判断该type是否已经被占用。
 */
void diaTestManager::getAllPorotocol(QSet<int>& sNumber)
{
    for(int i = 1; i < 16; i++)
    {
        QString strParameter = "_Protocol";
        QString strParameterName = configHelper::readInit("Name" ,strParameter.insert(0, QString::number(i)));
        if(strParameterName.isEmpty())
        {
            sNumber.insert(i); // 该类型未被占用！
        }
    }
}
