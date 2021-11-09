#include "diaaddnewparameter.h"
#include "ui_diaaddnewparameter.h"

DiaAddNewParameter::DiaAddNewParameter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaAddNewParameter)
{
    ui->setupUi(this);
    this->setWindowTitle("添加参数");

    // 查找已经删除的参数，从配置文件中删除
    QStringList slNumber;
    for(int i = 1; i < 16; i++)
    {
        QString strNumber = QString::number(i, 16).toUpper();
        slNumber.append(strNumber);

    }
    ui->comboBox_Number->addItems(slNumber);

    QRegExp rx("^[\u4E00-\u9FA5A-z][\u4E00-\u9FA5A-z0-9]+$");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->lineEdit_Name->setValidator(validator);
}

DiaAddNewParameter::~DiaAddNewParameter()
{
    delete ui;
}

/**
 * @brief DiaAddNewParameter::getParameterData
 * @return 元组 {参数名称，参数协议号，参数结果显示的后缀}
 * 将界面中设置的信息返回
 */
std::tuple<QString, QString, QString> DiaAddNewParameter::getParameterData()
{
    if(ui->lineEdit_Name->text().isEmpty())
    {

    }
    QString strName = ui->lineEdit_Name->text();
    QString strType = ui->comboBox_Number->currentText();
    QString strSuffix = ui->lineEdit_Suffix->text();
    return std::make_tuple(strName, strType, strSuffix);
}

/**
 * @brief DiaAddNewParameter::slot_pushButton_Add_clicked
 * 添加
 */
void DiaAddNewParameter::slot_pushButton_Add_clicked()
{
    this->accept();
}

/**
 * @brief DiaAddNewParameter::slot_pushButton_Cancel_clicked
 * 取消
 */
void DiaAddNewParameter::slot_pushButton_Cancel_clicked()
{
    this->close();
}
