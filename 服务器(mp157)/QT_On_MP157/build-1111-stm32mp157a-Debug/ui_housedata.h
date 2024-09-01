/********************************************************************************
** Form generated from reading UI file 'housedata.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOUSEDATA_H
#define UI_HOUSEDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HouseData
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QMainWindow *HouseData)
    {
        if (HouseData->objectName().isEmpty())
            HouseData->setObjectName(QString::fromUtf8("HouseData"));
        HouseData->resize(486, 854);
        centralwidget = new QWidget(HouseData);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 71, 41));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 140, 361, 91));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 18pt \"Ubuntu\";\n"
"background-color: rgb(186, 189, 182);"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 290, 361, 91));
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 18pt \"Ubuntu\";\n"
"background-color: rgb(186, 189, 182);"));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(60, 440, 361, 91));
        pushButton_4->setStyleSheet(QString::fromUtf8("font: 18pt \"Ubuntu\";\n"
"background-color: rgb(186, 189, 182);"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(60, 580, 361, 91));
        pushButton_5->setStyleSheet(QString::fromUtf8("font: 18pt \"Ubuntu\";\n"
"background-color: rgb(186, 189, 182);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 730, 121, 121));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(360, 0, 121, 121));
        HouseData->setCentralWidget(centralwidget);

        retranslateUi(HouseData);

        QMetaObject::connectSlotsByName(HouseData);
    } // setupUi

    void retranslateUi(QMainWindow *HouseData)
    {
        HouseData->setWindowTitle(QCoreApplication::translate("HouseData", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("HouseData", "<", nullptr));
        pushButton_2->setText(QCoreApplication::translate("HouseData", "201", nullptr));
        pushButton_3->setText(QCoreApplication::translate("HouseData", "202", nullptr));
        pushButton_4->setText(QCoreApplication::translate("HouseData", "203", nullptr));
        pushButton_5->setText(QCoreApplication::translate("HouseData", ".....", nullptr));
        label->setText(QCoreApplication::translate("HouseData", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("HouseData", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HouseData: public Ui_HouseData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOUSEDATA_H
