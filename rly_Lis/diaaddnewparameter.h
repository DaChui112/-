#ifndef DIAADDNEWPARAMETER_H
#define DIAADDNEWPARAMETER_H

#include <QDialog>
class tuple;

namespace Ui {
class DiaAddNewParameter;
}

class DiaAddNewParameter : public QDialog
{
    Q_OBJECT

public:
    explicit DiaAddNewParameter(QWidget *parent = nullptr);
    ~DiaAddNewParameter();
    std::tuple<QString, QString, QString> getParameterData();


private slots:
    void slot_pushButton_Add_clicked();

    void slot_pushButton_Cancel_clicked();

private:
    Ui::DiaAddNewParameter *ui;
};

#endif // DIAADDNEWPARAMETER_H
