/********************************************************************************
** Form generated from reading UI file 'diatestmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIATESTMANAGER_H
#define UI_DIATESTMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_diaTestManager
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit_Name;
    QLabel *label_2;
    QLineEdit *lineEdit_Code;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_Apply;
    QPushButton *pushButton_Cancel;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *diaTestManager)
    {
        if (diaTestManager->objectName().isEmpty())
            diaTestManager->setObjectName(QString::fromUtf8("diaTestManager"));
        diaTestManager->resize(304, 443);
        diaTestManager->setStyleSheet(QString::fromUtf8("*{font: normal 20px \342\200\234\345\276\256\350\275\257\351\233\205\351\273\221\342\200\235 ;}\n"
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
"}\n"
"\n"
".QLineEdit {\n"
"	border-radius:5px;\n"
"	padding: 10;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(diaTestManager);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(diaTestManager);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit_Name = new QLineEdit(diaTestManager);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_Name);

        label_2 = new QLabel(diaTestManager);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_Code = new QLineEdit(diaTestManager);
        lineEdit_Code->setObjectName(QString::fromUtf8("lineEdit_Code"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_Code);


        horizontalLayout->addLayout(formLayout);

        horizontalSpacer_2 = new QSpacerItem(23, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(32, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        groupBox = new QGroupBox(diaTestManager);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox);

        horizontalSpacer_4 = new QSpacerItem(23, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(32, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pushButton_Apply = new QPushButton(diaTestManager);
        pushButton_Apply->setObjectName(QString::fromUtf8("pushButton_Apply"));
        pushButton_Apply->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(pushButton_Apply);

        pushButton_Cancel = new QPushButton(diaTestManager);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setMinimumSize(QSize(100, 0));

        horizontalLayout_3->addWidget(pushButton_Cancel);

        horizontalSpacer_6 = new QSpacerItem(36, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(diaTestManager);
        QObject::connect(pushButton_Apply, SIGNAL(clicked()), diaTestManager, SLOT(slot_pushButton_Apply_clicked()));
        QObject::connect(pushButton_Cancel, SIGNAL(clicked()), diaTestManager, SLOT(slot_pushButton_Cancel_clicked()));

        QMetaObject::connectSlotsByName(diaTestManager);
    } // setupUi

    void retranslateUi(QDialog *diaTestManager)
    {
        diaTestManager->setWindowTitle(QCoreApplication::translate("diaTestManager", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("diaTestManager", "\351\241\271\347\233\256\345\220\215\347\247\260\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("diaTestManager", "\351\241\271\347\233\256\344\273\243\345\217\267\357\274\232", nullptr));
        groupBox->setTitle(QCoreApplication::translate("diaTestManager", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        pushButton_Apply->setText(QCoreApplication::translate("diaTestManager", "\345\272\224\347\224\250", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("diaTestManager", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class diaTestManager: public Ui_diaTestManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIATESTMANAGER_H
