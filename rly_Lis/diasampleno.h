#ifndef DIASAMPLENO_H
#define DIASAMPLENO_H

#include <QDialog>

namespace Ui {
class DiaSampleNo;
}

class DiaSampleNo : public QDialog
{
    Q_OBJECT

public:
    explicit DiaSampleNo(QWidget *parent = nullptr);
    ~DiaSampleNo();
    void getSampleNo(QString& strSampleNo);

private slots:
    void slot_pushButton_Add_clicked();
    void slot_pushButton_Cancel_clicked();

private:
    QString m_strSampleNo;  // 样本号
    Ui::DiaSampleNo *ui;
};

#endif // DIASAMPLENO_H
