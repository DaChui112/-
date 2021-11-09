/********************************************************************************
** Form generated from reading UI file 'diaaddtest.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAADDTEST_H
#define UI_DIAADDTEST_H

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

class Ui_diaAddTest
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Add;
    QPushButton *pushButton_Cancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *diaAddTest)
    {
        if (diaAddTest->objectName().isEmpty())
            diaAddTest->setObjectName(QString::fromUtf8("diaAddTest"));
        diaAddTest->resize(358, 140);
        verticalLayout = new QVBoxLayout(diaAddTest);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(diaAddTest);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(diaAddTest);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_Add = new QPushButton(diaAddTest);
        pushButton_Add->setObjectName(QString::fromUtf8("pushButton_Add"));

        horizontalLayout_2->addWidget(pushButton_Add);

        pushButton_Cancel = new QPushButton(diaAddTest);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));

        horizontalLayout_2->addWidget(pushButton_Cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(diaAddTest);

        QMetaObject::connectSlotsByName(diaAddTest);
    } // setupUi

    void retranslateUi(QDialog *diaAddTest)
    {
        diaAddTest->setWindowTitle(QCoreApplication::translate("diaAddTest", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("diaAddTest", "\345\220\215\347\247\260\357\274\232", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("diaAddTest", "\346\267\273\345\212\240", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("diaAddTest", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class diaAddTest: public Ui_diaAddTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAADDTEST_H
