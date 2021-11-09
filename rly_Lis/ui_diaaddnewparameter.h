/********************************************************************************
** Form generated from reading UI file 'diaaddnewparameter.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAADDNEWPARAMETER_H
#define UI_DIAADDNEWPARAMETER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DiaAddNewParameter
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit_Name;
    QLabel *label_2;
    QComboBox *comboBox_Number;
    QLabel *label_3;
    QLineEdit *lineEdit_Suffix;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Add;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Cancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *DiaAddNewParameter)
    {
        if (DiaAddNewParameter->objectName().isEmpty())
            DiaAddNewParameter->setObjectName(QString::fromUtf8("DiaAddNewParameter"));
        DiaAddNewParameter->resize(305, 217);
        DiaAddNewParameter->setStyleSheet(QString::fromUtf8("*{font: normal 20px \342\200\234\345\276\256\350\275\257\351\233\205\351\273\221\342\200\235 ;}\n"
"\n"
"QWidget#diaTestManager {\n"
"	background-color: #eaeaea;\n"
"}\n"
"\n"
".QLabel {\n"
"	padding: 10px;\n"
"	border-radius: 5px;\n"
"}\n"
"\n"
".QPushButton {\n"
"	border: 1px solid;\n"
"	background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #e9e9e9,stop:1 #f2f2f3);\n"
"	padding: 10px;\n"
"	border-radius: 5px;\n"
"}\n"
"\n"
".QPushButton:hover {\n"
"    background-color: #ecf5ff;\n"
"    color: #409eff;\n"
"}\n"
"\n"
".QPushButton:pressed, QPushButton:checked {\n"
"    border: 1px solid #3a8ee6;\n"
"    color: #409eff;\n"
"}\n"
"\n"
".QTableWidget{\n"
"	color: #000000;\n"
"	alternate-background-color: #e0e0e0;\n"
"}\n"
"\n"
".QTableWidget::item:selected {\n"
"	color: #000000; \n"
"	background-color: #8fcde6;\n"
"\n"
"}\n"
"\n"
".QComboBox {\n"
"	background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #e9e9e9,stop:1 #f2f2f3);\n"
"  	padding: 10;\n"
" 	border:1px solid rgba(228,2"
                        "28,228,1);\n"
"	border-radius:5px;\n"
"	font:20px;\n"
"}\n"
"\n"
".QLineEdit {\n"
"	border-radius:5px;\n"
"	padding: 10;\n"
"	font:20px;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(DiaAddNewParameter);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(DiaAddNewParameter);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit_Name = new QLineEdit(DiaAddNewParameter);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_Name);

        label_2 = new QLabel(DiaAddNewParameter);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        comboBox_Number = new QComboBox(DiaAddNewParameter);
        comboBox_Number->setObjectName(QString::fromUtf8("comboBox_Number"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBox_Number);

        label_3 = new QLabel(DiaAddNewParameter);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        lineEdit_Suffix = new QLineEdit(DiaAddNewParameter);
        lineEdit_Suffix->setObjectName(QString::fromUtf8("lineEdit_Suffix"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_Suffix);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_Add = new QPushButton(DiaAddNewParameter);
        pushButton_Add->setObjectName(QString::fromUtf8("pushButton_Add"));
        pushButton_Add->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton_Add);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Cancel = new QPushButton(DiaAddNewParameter);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton_Cancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DiaAddNewParameter);
        QObject::connect(pushButton_Cancel, SIGNAL(clicked()), DiaAddNewParameter, SLOT(slot_pushButton_Cancel_clicked()));
        QObject::connect(pushButton_Add, SIGNAL(clicked()), DiaAddNewParameter, SLOT(slot_pushButton_Add_clicked()));

        QMetaObject::connectSlotsByName(DiaAddNewParameter);
    } // setupUi

    void retranslateUi(QDialog *DiaAddNewParameter)
    {
        DiaAddNewParameter->setWindowTitle(QCoreApplication::translate("DiaAddNewParameter", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DiaAddNewParameter", "\345\217\202\346\225\260\345\220\215\347\247\260\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("DiaAddNewParameter", "\345\215\217\350\256\256\345\217\267\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("DiaAddNewParameter", "\347\273\223\346\236\234\345\220\216\347\274\200\357\274\232", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("DiaAddNewParameter", "\346\267\273\345\212\240", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("DiaAddNewParameter", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiaAddNewParameter: public Ui_DiaAddNewParameter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAADDNEWPARAMETER_H
