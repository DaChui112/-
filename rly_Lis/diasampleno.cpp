#include "diasampleno.h"
#include "ui_diasampleno.h"

#include <QRegExp>
#include <QValidator>

DiaSampleNo::DiaSampleNo(QWidget *parent) :
    QDialog(parent),
    m_strSampleNo(""),
    ui(new Ui::DiaSampleNo)
{
    ui->setupUi(this);
    this->setWindowTitle("添加样本号");

    QRegExp rx("[0-9]{15}");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->lineEdit->setValidator(validator);
}

DiaSampleNo::~DiaSampleNo()
{
    delete ui;
}

/**
 * @brief DiaSampleNo::getSampleNo
 * @param m_strSampleNo OUT
 * 返回样本号
 */
void DiaSampleNo::getSampleNo(QString &m_strSampleNo)
{
    m_strSampleNo = this->m_strSampleNo;
}

/**
 * @brief DiaSampleNo::slot_pushButton_Add_clicked
 * 应用
 */
void DiaSampleNo::slot_pushButton_Add_clicked()
{
    m_strSampleNo = ui->lineEdit->text();
    this->accept();
}

/**
 * @brief DiaSampleNo::slot_pushButton_Cancel_clicked
 * 取消
 */
void DiaSampleNo::slot_pushButton_Cancel_clicked()
{
    this->close();
}

