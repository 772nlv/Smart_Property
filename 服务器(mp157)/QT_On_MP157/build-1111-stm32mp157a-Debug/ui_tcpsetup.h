/********************************************************************************
** Form generated from reading UI file 'tcpsetup.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSETUP_H
#define UI_TCPSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpSetup
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QSplitter *splitter;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSplitter *splitter_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QSplitter *splitter_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *TcpSetup)
    {
        if (TcpSetup->objectName().isEmpty())
            TcpSetup->setObjectName(QString::fromUtf8("TcpSetup"));
        TcpSetup->resize(484, 872);
        centralwidget = new QWidget(TcpSetup);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(50, 50, 381, 191));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(136, 138, 133);\n"
"background-color: rgb(186, 189, 182);"));
        splitter = new QSplitter(widget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(20, 70, 81, 101));
        splitter->setOrientation(Qt::Vertical);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 215, 207);\n"
"font: 15pt \"Ubuntu\";"));
        splitter->addWidget(label);
        label_2 = new QLabel(splitter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 189, 182);\n"
"font: 15pt \"Ubuntu\";\n"
"background-color: rgb(211, 215, 207);"));
        splitter->addWidget(label_2);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 10, 141, 41));
        label_3->setStyleSheet(QString::fromUtf8("font: 13pt \"Ubuntu\";\n"
"background-color: rgb(136, 138, 133);"));
        splitter_2 = new QSplitter(widget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(120, 70, 241, 101));
        splitter_2->setOrientation(Qt::Vertical);
        lineEdit = new QLineEdit(splitter_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);\n"
"font: 13pt \"Ubuntu\";"));
        splitter_2->addWidget(lineEdit);
        lineEdit_2 = new QLineEdit(splitter_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 215, 207);\n"
"font: 13pt \"Ubuntu\";\n"
"background-color: rgb(238, 238, 236);"));
        splitter_2->addWidget(lineEdit_2);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 71, 41));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 250, 441, 451));
        textEdit->setStyleSheet(QString::fromUtf8("font: 13pt \"Ubuntu\";"));
        splitter_3 = new QSplitter(centralwidget);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setGeometry(QRect(80, 750, 321, 61));
        splitter_3->setOrientation(Qt::Horizontal);
        pushButton_3 = new QPushButton(splitter_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        splitter_3->addWidget(pushButton_3);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(360, 700, 101, 41));
        TcpSetup->setCentralWidget(centralwidget);

        retranslateUi(TcpSetup);

        QMetaObject::connectSlotsByName(TcpSetup);
    } // setupUi

    void retranslateUi(QMainWindow *TcpSetup)
    {
        TcpSetup->setWindowTitle(QCoreApplication::translate("TcpSetup", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("TcpSetup", "IP:", nullptr));
        label_2->setText(QCoreApplication::translate("TcpSetup", "port:", nullptr));
        label_3->setText(QCoreApplication::translate("TcpSetup", "Server_set", nullptr));
        lineEdit->setText(QCoreApplication::translate("TcpSetup", "192.168.30.222", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("TcpSetup", "6666", nullptr));
        pushButton->setText(QCoreApplication::translate("TcpSetup", "<", nullptr));
        pushButton_3->setText(QCoreApplication::translate("TcpSetup", "Close_Server", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TcpSetup", "\346\270\205\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpSetup: public Ui_TcpSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSETUP_H
