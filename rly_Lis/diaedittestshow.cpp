#include "diaedittestshow.h"
#include "ui_diaedittestshow.h"
#include "sqlhelper.h"
#include "diaaddnewparameter.h"
#include <QMessageBox>
#include <tuple>

DiaEditTestShow::DiaEditTestShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaEditTestShow)
{
    ui->setupUi(this);
    db = sqlhelper::getSingleton();
    Init();
    UpdateParameter();
}

DiaEditTestShow::~DiaEditTestShow()
{
    delete ui;
}

void DiaEditTestShow::Init()
{
    setWindowTitle("参数管理");
    // 初始化参数列表
    ui->tableWidget_Test->setColumnCount(1);
    ui->tableWidget_Test->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    QStringList slheader;
    slheader<<"参数列表";
    ui->tableWidget_Test->setHorizontalHeaderLabels(slheader);
    ui->tableWidget_Test->verticalHeader()->setVisible(false);
    ui->tableWidget_Test->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    ui->tableWidget_Test->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Test->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Test->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Test->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget_Test->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_Test->horizontalHeader()->setStretchLastSection(true);

    // 初始化未启用参数列表
    ui->tableWidget_disTest->setColumnCount(1);
    ui->tableWidget_disTest->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    slheader.clear();
    slheader<<"未启用参数";
    ui->tableWidget_disTest->setHorizontalHeaderLabels(slheader);
    ui->tableWidget_disTest->verticalHeader()->setVisible(false);
    ui->tableWidget_disTest->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    ui->tableWidget_disTest->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_disTest->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_disTest->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_disTest->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_disTest->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget_disTest->horizontalHeader()->setStretchLastSection(true);

    // 初始化启用参数列表
    ui->tableWidget_EnableTest->setColumnCount(1);
    ui->tableWidget_EnableTest->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    slheader.clear();
    slheader<<"已启用参数";
    ui->tableWidget_EnableTest->setHorizontalHeaderLabels(slheader);
    ui->tableWidget_EnableTest->verticalHeader()->setVisible(false);
    ui->tableWidget_EnableTest->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:rgb(220,221,221);border-color:rgb(200,199,199);border-style:solid;border-width:1px;}");
    ui->tableWidget_EnableTest->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_EnableTest->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_EnableTest->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_EnableTest->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget_EnableTest->verticalHeader()->setDefaultSectionSize(40);
    ui->tableWidget_EnableTest->horizontalHeader()->setStretchLastSection(true);
}

/**
 * @brief DiaEditTestShow::UpdateParameter
 * 根据项目参数开启/关闭状态来刷新表格
 */
void DiaEditTestShow::UpdateParameter()
{
    db->getAllParameters(m_parameter_info);
    // 更新参数表格
    int rows = m_parameter_info.size();
    for(int row = 0; row < rows; row++)
    {
        AddTableItem(ui->tableWidget_Test, m_parameter_info.at(row)["parameter"]);
        m_sParameter.insert(m_parameter_info.at(row)["parameter"]);

        if("1" != m_parameter_info.at(row)["isOpen"])
        {
            AddTableItem(ui->tableWidget_disTest, m_parameter_info.at(row)["parameter"]);
        }
        else
        {
            AddTableItem(ui->tableWidget_EnableTest, m_parameter_info.at(row)["parameter"]);
        }
    }
}

/**
 * @brief DiaEditTestShow::AddTableItem
 * 在需要操作的QTableWidget的最后一行添加一个Item。
 * @param tab 需要操作的QTableWidget
 * @param strParameter 需要添加的字段
 */
void DiaEditTestShow::AddTableItem(QTableWidget *tab, const QString &strParameter)
{
    int row = tab->rowCount();
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(strParameter);
    item->setTextAlignment(Qt::AlignCenter);
    tab->insertRow(row);
    tab->setItem(row, 0, item);
}

/**
 * @brief DiaEditTestShow::DelTableItem
 * 根据strParameter删除TabWidget中的组件
 * @param tab QTableWidget
 * @param strParameter item的text属性
 */
void DiaEditTestShow::DelTableItem(QTableWidget *tab, const QString &strParameter)
{
    if(strParameter.isEmpty())
    {
        return;
    }
    auto lItems = tab->findItems(strParameter, Qt::MatchExactly);
    if(lItems.isEmpty())
    {
        return;
    }
    tab->removeRow(lItems.first()->row());
}

/**
 * @brief DiaEditTestShow::slot_pushButton_AddTest_clicked
 * 添加新参数
 */
void DiaEditTestShow::slot_pushButton_AddTest_clicked()
{
    DiaAddNewParameter diaaddnewparameter;
    if(diaaddnewparameter.exec() == QDialog::Accepted)
    {
        QString strParameterName, strParameterType, strParameterSuffix;
        std::tie(strParameterName, strParameterType, strParameterSuffix)
                = diaaddnewparameter.getParameterData();
        if(m_sParameter.contains(strParameterName))
        {
            QMessageBox::warning(this, "警告", "该参数名称已经存在！");
            return;
        }
        strParameterType += "_Protocol";
        if(configHelper::readInit("Name", strParameterType) != "")
        {
            QMessageBox::warning(this, "警告", "该协议类型已经存在！");
            return;
        }
        QHash<QString,QString> hsParameter;
        hsParameter["Name"] = strParameterName;
        hsParameter["Suffix"] = strParameterSuffix;
        hsParameter["Type"] = strParameterType;
        m_protocol.append(hsParameter);

        m_sParameter.insert(strParameterName);
        AddTableItem(ui->tableWidget_Test, strParameterName);
        AddTableItem(ui->tableWidget_disTest, strParameterName);
    }
}

/**
 * @brief DiaEditTestShow::slot_pushButton_DelTest_clicked
 * 删除参数
 */
void DiaEditTestShow::slot_pushButton_DelTest_clicked()
{
    if(ui->tableWidget_Test->currentItem() == nullptr)
    {
        return;
    }
    QString strParameter = ui->tableWidget_Test->currentItem()->text();
    DelTableItem(ui->tableWidget_Test, strParameter);
    DelTableItem(ui->tableWidget_disTest, strParameter);
    DelTableItem(ui->tableWidget_EnableTest, strParameter);
    m_sParameter.erase(m_sParameter.find(strParameter));
}

/**
 * @brief DiaEditTestShow::slot_pushButton_Apply_clicked
 * 应用，此处开始更新数据库及配置文件数据
 */
void DiaEditTestShow::slot_pushButton_Apply_clicked()
{
    // 从数据库删除已经删除的参数
    db->delColToItem(m_sParameter);
    // 添加新增项目
    auto sParas = m_sParameter;
    int size = m_parameter_info.size();
    for(int i = 0; i < size; i++)
    {
        auto it = sParas.find(m_parameter_info.at(i)["parameter"]);
        if(it != sParas.end())
        {
            sParas.erase(it);
        }
    }
    foreach (QString strPara, sParas) {
        db->addColToItem(strPara, "");
    }
    // 更新项目启用关闭
    QList<QHash<QString, QString>> data;
    auto getHashData = [&data](QTableWidget* tab, QString strFlag){
        int rows = tab->rowCount();
        for(int row = 0; row < rows; row++)
        {
            QHash<QString, QString> hsData;
            hsData["parameter"] = tab->item(row, 0)->text();
            hsData["isOpen"] = strFlag;
            data.append(hsData);
        }
    };
    getHashData(ui->tableWidget_disTest, "0");
    getHashData(ui->tableWidget_EnableTest, "1");
    db->updateparameter_enable(data);
    // 查找已经删除的参数，从配置文件中删除
    for(int i = 1; i < 16; i++)
    {
        QString strNumber = QString::number(i, 16).toUpper();
        strNumber += "_Protocol";
        if(!m_sParameter.contains(configHelper::readInit("Name", strNumber)))
        {
            configHelper::DeleteInitConfig(strNumber);
        }
    }
    // 写入配置文件
    for(auto hash: m_protocol)
    {
        if(!configHelper::writeInit(hash, hash["Type"]))
        {
            QMessageBox::warning(this, "警告", "参数添加失败，未知错误！");
            return;
        }
    }
    this->accept();
}

/**
 * @brief DiaEditTestShow::slot_pushButton_Cancel_clicked
 * 取消
 */
void DiaEditTestShow::slot_pushButton_Cancel_clicked()
{
    this->close();
}

/**
 * @brief DiaEditTestShow::slot_pushButton_Add_clicked
 * 使所选参数变为开启状态
 */
void DiaEditTestShow::slot_pushButton_Add_clicked()
{
    if(ui->tableWidget_disTest->currentItem() == nullptr)
    {
        return;
    }
    auto strParameter = ui->tableWidget_disTest->currentItem()->text();
    AddTableItem(ui->tableWidget_EnableTest, strParameter);
    DelTableItem(ui->tableWidget_disTest, strParameter);
}

/**
 * @brief DiaEditTestShow::slot_pushButton_Del_clicked
 * 使所选参数变为关闭状态
 */
void DiaEditTestShow::slot_pushButton_Del_clicked()
{
    if(ui->tableWidget_EnableTest->currentItem() == nullptr)
    {
        return;
    }
    auto strParameter = ui->tableWidget_EnableTest->currentItem()->text();
    AddTableItem(ui->tableWidget_disTest, strParameter);
    DelTableItem(ui->tableWidget_EnableTest, strParameter);
}
