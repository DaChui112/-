/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *comboBox_com;
    QLabel *label_2;
    QComboBox *comboBox_rate;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_SerialOpen;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_sIP;
    QComboBox *comboBox_IP;
    QLabel *label_sPort;
    QLineEdit *lineEdit_sPort;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Listen;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_DeleteSample;
    QTableWidget *tableWidget_sampleNo;
    QPushButton *pushButton_AddSample;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_ClearTestResult;
    QTableWidget *tableWidget_result;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tableWidget_Test;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_AddTest;
    QPushButton *pushButton_DeleteTest;
    QPushButton *pushButton_SendTest;
    QPushButton *pushButton_Edit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1300, 700);
        MainWindow->setStyleSheet(QString::fromUtf8("*{font: normal 20px \342\200\234\345\276\256\350\275\257\351\233\205\351\273\221\342\200\235 ;}\n"
"\n"
"QWidget#centralwidget {\n"
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
" 	border:1px solid rgba(228,22"
                        "8,228,1);\n"
"	border-radius:5px;\n"
"}\n"
"\n"
".QLineEdit {\n"
"	border-radius:5px;\n"
"	padding: 10;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        formLayout = new QFormLayout(groupBox_3);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\342\200\234\345\276\256\350\275\257\351\233\205\351\273\221\342\200\235"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        comboBox_com = new QComboBox(groupBox_3);
        comboBox_com->setObjectName(QString::fromUtf8("comboBox_com"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_com->sizePolicy().hasHeightForWidth());
        comboBox_com->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox_com);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        comboBox_rate = new QComboBox(groupBox_3);
        comboBox_rate->addItem(QString());
        comboBox_rate->addItem(QString());
        comboBox_rate->addItem(QString());
        comboBox_rate->setObjectName(QString::fromUtf8("comboBox_rate"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboBox_rate);

        horizontalSpacer_4 = new QSpacerItem(94, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(2, QFormLayout::LabelRole, horizontalSpacer_4);

        pushButton_SerialOpen = new QPushButton(groupBox_3);
        pushButton_SerialOpen->setObjectName(QString::fromUtf8("pushButton_SerialOpen"));
        pushButton_SerialOpen->setFont(font);

        formLayout->setWidget(2, QFormLayout::FieldRole, pushButton_SerialOpen);


        verticalLayout->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setRowWrapPolicy(QFormLayout::DontWrapRows);
        formLayout_2->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout_2->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_sIP = new QLabel(groupBox_2);
        label_sIP->setObjectName(QString::fromUtf8("label_sIP"));
        label_sIP->setFont(font);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_sIP);

        comboBox_IP = new QComboBox(groupBox_2);
        comboBox_IP->setObjectName(QString::fromUtf8("comboBox_IP"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, comboBox_IP);

        label_sPort = new QLabel(groupBox_2);
        label_sPort->setObjectName(QString::fromUtf8("label_sPort"));
        label_sPort->setFont(font);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_sPort);

        lineEdit_sPort = new QLineEdit(groupBox_2);
        lineEdit_sPort->setObjectName(QString::fromUtf8("lineEdit_sPort"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEdit_sPort);

        horizontalSpacer = new QSpacerItem(79, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_2->setItem(2, QFormLayout::LabelRole, horizontalSpacer);

        pushButton_Listen = new QPushButton(groupBox_2);
        pushButton_Listen->setObjectName(QString::fromUtf8("pushButton_Listen"));
        pushButton_Listen->setFont(font);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, pushButton_Listen);


        verticalLayout->addWidget(groupBox_2);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButton_DeleteSample = new QPushButton(centralwidget);
        pushButton_DeleteSample->setObjectName(QString::fromUtf8("pushButton_DeleteSample"));
        pushButton_DeleteSample->setFont(font);

        gridLayout_5->addWidget(pushButton_DeleteSample, 1, 1, 1, 1);

        tableWidget_sampleNo = new QTableWidget(centralwidget);
        tableWidget_sampleNo->setObjectName(QString::fromUtf8("tableWidget_sampleNo"));

        gridLayout_5->addWidget(tableWidget_sampleNo, 0, 0, 1, 2);

        pushButton_AddSample = new QPushButton(centralwidget);
        pushButton_AddSample->setObjectName(QString::fromUtf8("pushButton_AddSample"));
        pushButton_AddSample->setFont(font);

        gridLayout_5->addWidget(pushButton_AddSample, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_5);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_3 = new QSpacerItem(281, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        pushButton_ClearTestResult = new QPushButton(groupBox);
        pushButton_ClearTestResult->setObjectName(QString::fromUtf8("pushButton_ClearTestResult"));
        pushButton_ClearTestResult->setFont(font);

        gridLayout->addWidget(pushButton_ClearTestResult, 1, 1, 1, 1);

        tableWidget_result = new QTableWidget(groupBox);
        tableWidget_result->setObjectName(QString::fromUtf8("tableWidget_result"));
        tableWidget_result->setMaximumSize(QSize(16777215, 16777215));
        tableWidget_result->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget_result->setTextElideMode(Qt::ElideRight);

        gridLayout->addWidget(tableWidget_result, 0, 0, 1, 2);


        verticalLayout_2->addWidget(groupBox);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tableWidget_Test = new QTableWidget(groupBox_4);
        tableWidget_Test->setObjectName(QString::fromUtf8("tableWidget_Test"));

        verticalLayout_3->addWidget(tableWidget_Test);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_AddTest = new QPushButton(groupBox_4);
        pushButton_AddTest->setObjectName(QString::fromUtf8("pushButton_AddTest"));
        pushButton_AddTest->setFont(font);

        horizontalLayout->addWidget(pushButton_AddTest);

        pushButton_DeleteTest = new QPushButton(groupBox_4);
        pushButton_DeleteTest->setObjectName(QString::fromUtf8("pushButton_DeleteTest"));
        pushButton_DeleteTest->setFont(font);

        horizontalLayout->addWidget(pushButton_DeleteTest);

        pushButton_SendTest = new QPushButton(groupBox_4);
        pushButton_SendTest->setObjectName(QString::fromUtf8("pushButton_SendTest"));
        pushButton_SendTest->setFont(font);

        horizontalLayout->addWidget(pushButton_SendTest);

        pushButton_Edit = new QPushButton(groupBox_4);
        pushButton_Edit->setObjectName(QString::fromUtf8("pushButton_Edit"));
        pushButton_Edit->setFont(font);

        horizontalLayout->addWidget(pushButton_Edit);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(groupBox_4);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 4);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_SerialOpen, SIGNAL(clicked()), MainWindow, SLOT(slot_btn_SerialOpen_clicked()));
        QObject::connect(pushButton_Listen, SIGNAL(clicked()), MainWindow, SLOT(slot_btn_Listen_clicked()));
        QObject::connect(pushButton_AddTest, SIGNAL(clicked()), MainWindow, SLOT(slot_btn_AddTest_clicked()));
        QObject::connect(pushButton_DeleteTest, SIGNAL(clicked()), MainWindow, SLOT(slot_btn_DeleteTest_clicked()));
        QObject::connect(pushButton_SendTest, SIGNAL(clicked()), MainWindow, SLOT(slot_btn_SendTest_clicked()));
        QObject::connect(pushButton_Edit, SIGNAL(clicked()), MainWindow, SLOT(slot_btn_Edit_clicked()));
        QObject::connect(pushButton_ClearTestResult, SIGNAL(clicked()), MainWindow, SLOT(slot_btn_ClearTestResult_clicked()));
        QObject::connect(pushButton_AddSample, SIGNAL(clicked()), MainWindow, SLOT(slot_btn_AddSample_clicked()));
        QObject::connect(pushButton_DeleteSample, SIGNAL(clicked()), MainWindow, SLOT(slot_btn_DeleteSample_clicked()));
        QObject::connect(tableWidget_Test, SIGNAL(cellDoubleClicked(int,int)), MainWindow, SLOT(slot_tableWidget_Test_cellDoubleClicked(int,int)));
        QObject::connect(tableWidget_Test, SIGNAL(cellClicked(int,int)), MainWindow, SLOT(slot_tableWidget_Test_cellClicked(int,int)));
        QObject::connect(tableWidget_sampleNo, SIGNAL(currentCellChanged(int,int,int,int)), MainWindow, SLOT(slot_tableWidget_sampleNo_currentCellChanged(int,int,int,int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\346\250\241\345\274\217", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        comboBox_rate->setItemText(0, QCoreApplication::translate("MainWindow", "9600", nullptr));
        comboBox_rate->setItemText(1, QCoreApplication::translate("MainWindow", "38400", nullptr));
        comboBox_rate->setItemText(2, QCoreApplication::translate("MainWindow", "115200", nullptr));

        pushButton_SerialOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "TCP\346\250\241\345\274\217", nullptr));
        label_sIP->setText(QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260IP\357\274\232", nullptr));
        label_sPort->setText(QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260\347\253\257\345\217\243\357\274\232", nullptr));
        pushButton_Listen->setText(QCoreApplication::translate("MainWindow", "\347\233\221\345\220\254", nullptr));
        pushButton_DeleteSample->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\240\267\346\234\254\345\217\267", nullptr));
        pushButton_AddSample->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\240\267\346\234\254\345\217\267", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225\347\273\223\346\236\234", nullptr));
        pushButton_ClearTestResult->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\265\213\350\257\225\347\273\223\346\236\234", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225\351\241\271\347\233\256", nullptr));
        pushButton_AddTest->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\351\241\271\347\233\256", nullptr));
        pushButton_DeleteTest->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\351\241\271\347\233\256", nullptr));
        pushButton_SendTest->setText(QCoreApplication::translate("MainWindow", "\345\256\236\351\252\214\344\270\213\345\217\221", nullptr));
        pushButton_Edit->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\347\273\204\345\220\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
