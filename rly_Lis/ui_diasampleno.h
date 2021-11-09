/********************************************************************************
** Form generated from reading UI file 'diasampleno.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIASAMPLENO_H
#define UI_DIASAMPLENO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DiaSampleNo
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Add;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Cancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *DiaSampleNo)
    {
        if (DiaSampleNo->objectName().isEmpty())
            DiaSampleNo->setObjectName(QString::fromUtf8("DiaSampleNo"));
        DiaSampleNo->resize(337, 151);
        DiaSampleNo->setStyleSheet(QString::fromUtf8("*{font: normal 20px \342\200\234\345\276\256\350\275\257\351\233\205\351\273\221\342\200\235 ;}\n"
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
        verticalLayout = new QVBoxLayout(DiaSampleNo);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label = new QLabel(DiaSampleNo);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(DiaSampleNo);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Add = new QPushButton(DiaSampleNo);
        pushButton_Add->setObjectName(QString::fromUtf8("pushButton_Add"));
        pushButton_Add->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton_Add);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_Cancel = new QPushButton(DiaSampleNo);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton_Cancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DiaSampleNo);
        QObject::connect(pushButton_Add, SIGNAL(clicked()), DiaSampleNo, SLOT(slot_pushButton_Add_clicked()));
        QObject::connect(pushButton_Cancel, SIGNAL(clicked()), DiaSampleNo, SLOT(slot_pushButton_Cancel_clicked()));

        QMetaObject::connectSlotsByName(DiaSampleNo);
    } // setupUi

    void retranslateUi(QDialog *DiaSampleNo)
    {
        DiaSampleNo->setWindowTitle(QCoreApplication::translate("DiaSampleNo", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DiaSampleNo", "\346\240\267\346\234\254\345\217\267\357\274\232", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("DiaSampleNo", "\346\267\273\345\212\240", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("DiaSampleNo", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiaSampleNo: public Ui_DiaSampleNo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIASAMPLENO_H
