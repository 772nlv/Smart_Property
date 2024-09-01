/********************************************************************************
** Form generated from reading UI file 'house_201.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOUSE_201_H
#define UI_HOUSE_201_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_House_201
{
public:
    QWidget *centralwidget;
    QTableView *tableView;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *House_201)
    {
        if (House_201->objectName().isEmpty())
            House_201->setObjectName(QString::fromUtf8("House_201"));
        House_201->resize(496, 856);
        centralwidget = new QWidget(House_201);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(20, 110, 451, 641));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 81, 41));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(370, 0, 121, 111));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(120, 770, 231, 71));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 14pt \"Ubuntu\";"));
        House_201->setCentralWidget(centralwidget);

        retranslateUi(House_201);

        QMetaObject::connectSlotsByName(House_201);
    } // setupUi

    void retranslateUi(QMainWindow *House_201)
    {
        House_201->setWindowTitle(QCoreApplication::translate("House_201", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("House_201", "<", nullptr));
        label->setText(QCoreApplication::translate("House_201", "TextLabel", nullptr));
        pushButton_2->setText(QCoreApplication::translate("House_201", "\350\216\267\345\217\226\344\277\241\346\201\257(\345\210\267\346\226\260)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class House_201: public Ui_House_201 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOUSE_201_H
