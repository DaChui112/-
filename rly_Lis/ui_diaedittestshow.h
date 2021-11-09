/********************************************************************************
** Form generated from reading UI file 'diaedittestshow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAEDITTESTSHOW_H
#define UI_DIAEDITTESTSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DiaEditTestShow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tableWidget_Test;
    QPushButton *pushButton_AddTest;
    QPushButton *pushButton_DelTest;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget_disTest;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_Add;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_Del;
    QSpacerItem *verticalSpacer_3;
    QTableWidget *tableWidget_EnableTest;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Apply;
    QPushButton *pushButton_Cancel;

    void setupUi(QDialog *DiaEditTestShow)
    {
        if (DiaEditTestShow->objectName().isEmpty())
            DiaEditTestShow->setObjectName(QString::fromUtf8("DiaEditTestShow"));
        DiaEditTestShow->resize(811, 606);
        DiaEditTestShow->setStyleSheet(QString::fromUtf8("*{font: normal 20px \342\200\234\345\276\256\350\275\257\351\233\205\351\273\221\342\200\235 ;}\n"
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
        verticalLayout = new QVBoxLayout(DiaEditTestShow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox = new QGroupBox(DiaEditTestShow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tableWidget_Test = new QTableWidget(groupBox);
        tableWidget_Test->setObjectName(QString::fromUtf8("tableWidget_Test"));

        verticalLayout_3->addWidget(tableWidget_Test);

        pushButton_AddTest = new QPushButton(groupBox);
        pushButton_AddTest->setObjectName(QString::fromUtf8("pushButton_AddTest"));

        verticalLayout_3->addWidget(pushButton_AddTest);

        pushButton_DelTest = new QPushButton(groupBox);
        pushButton_DelTest->setObjectName(QString::fromUtf8("pushButton_DelTest"));
        pushButton_DelTest->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_DelTest->sizePolicy().hasHeightForWidth());
        pushButton_DelTest->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(pushButton_DelTest);


        horizontalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(DiaEditTestShow);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget_disTest = new QTableWidget(groupBox_2);
        tableWidget_disTest->setObjectName(QString::fromUtf8("tableWidget_disTest"));

        horizontalLayout->addWidget(tableWidget_disTest);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        pushButton_Add = new QPushButton(groupBox_2);
        pushButton_Add->setObjectName(QString::fromUtf8("pushButton_Add"));
        pushButton_Add->setMinimumSize(QSize(60, 60));

        verticalLayout_2->addWidget(pushButton_Add);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        pushButton_Del = new QPushButton(groupBox_2);
        pushButton_Del->setObjectName(QString::fromUtf8("pushButton_Del"));
        pushButton_Del->setMinimumSize(QSize(60, 60));

        verticalLayout_2->addWidget(pushButton_Del);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);


        horizontalLayout->addLayout(verticalLayout_2);

        tableWidget_EnableTest = new QTableWidget(groupBox_2);
        tableWidget_EnableTest->setObjectName(QString::fromUtf8("tableWidget_EnableTest"));

        horizontalLayout->addWidget(tableWidget_EnableTest);


        horizontalLayout_3->addWidget(groupBox_2);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_Apply = new QPushButton(DiaEditTestShow);
        pushButton_Apply->setObjectName(QString::fromUtf8("pushButton_Apply"));
        pushButton_Apply->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(pushButton_Apply);

        pushButton_Cancel = new QPushButton(DiaEditTestShow);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(pushButton_Cancel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(DiaEditTestShow);
        QObject::connect(pushButton_AddTest, SIGNAL(clicked()), DiaEditTestShow, SLOT(slot_pushButton_AddTest_clicked()));
        QObject::connect(pushButton_Apply, SIGNAL(clicked()), DiaEditTestShow, SLOT(slot_pushButton_Apply_clicked()));
        QObject::connect(pushButton_Cancel, SIGNAL(clicked()), DiaEditTestShow, SLOT(slot_pushButton_Cancel_clicked()));
        QObject::connect(pushButton_Del, SIGNAL(clicked()), DiaEditTestShow, SLOT(slot_pushButton_Del_clicked()));
        QObject::connect(pushButton_Add, SIGNAL(clicked()), DiaEditTestShow, SLOT(slot_pushButton_Add_clicked()));
        QObject::connect(tableWidget_Test, SIGNAL(itemClicked(QTableWidgetItem*)), DiaEditTestShow, SLOT(slot_tableWidget_Test_itemClicked(QTableWidgetItem*)));
        QObject::connect(pushButton_DelTest, SIGNAL(clicked()), DiaEditTestShow, SLOT(slot_pushButton_DelTest_clicked()));

        QMetaObject::connectSlotsByName(DiaEditTestShow);
    } // setupUi

    void retranslateUi(QDialog *DiaEditTestShow)
    {
        DiaEditTestShow->setWindowTitle(QCoreApplication::translate("DiaEditTestShow", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DiaEditTestShow", "\346\265\213\350\257\225\351\241\271\347\256\241\347\220\206", nullptr));
        pushButton_AddTest->setText(QCoreApplication::translate("DiaEditTestShow", "\346\226\260\345\242\236\346\265\213\350\257\225\351\241\271", nullptr));
        pushButton_DelTest->setText(QCoreApplication::translate("DiaEditTestShow", "\345\210\240\351\231\244\346\265\213\350\257\225\351\241\271", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DiaEditTestShow", "\346\230\257\345\220\246\345\220\257\347\224\250", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("DiaEditTestShow", ">>", nullptr));
        pushButton_Del->setText(QCoreApplication::translate("DiaEditTestShow", "<<", nullptr));
        pushButton_Apply->setText(QCoreApplication::translate("DiaEditTestShow", "\345\272\224\347\224\250", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("DiaEditTestShow", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiaEditTestShow: public Ui_DiaEditTestShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAEDITTESTSHOW_H
