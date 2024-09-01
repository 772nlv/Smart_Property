/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QPlainTextEdit *plainTextEdit_2;
    QPushButton *pushButton;
    QLabel *label_2;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(486, 866);
        LoginWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 215, 207);"));
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 20, 361, 141));
        label->setStyleSheet(QString::fromUtf8("font: 57 17pt \"Ubuntu\";\n"
"background-color: rgb(186, 189, 182);"));
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(40, 200, 411, 151));
        plainTextEdit->setStyleSheet(QString::fromUtf8("font: 57 italic 25pt \"Ubuntu\";\n"
"background-color: rgb(211, 215, 207);\n"
"border-width: 0px;"));
        plainTextEdit_2 = new QPlainTextEdit(centralwidget);
        plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(40, 400, 411, 131));
        plainTextEdit_2->setStyleSheet(QString::fromUtf8("font: 20pt \"Ubuntu\";"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(130, 590, 211, 81));
        pushButton->setStyleSheet(QString::fromUtf8("font: 11pt \"Ubuntu\";\n"
"font: 57 italic 20pt \"Ubuntu\";"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(340, 710, 131, 121));
        LoginWindow->setCentralWidget(centralwidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "LOGO", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("LoginWindow", " \346\231\272\346\205\247\347\211\251\344\270\232\347\263\273\347\273\237\n"
"   --\346\234\215\345\212\241\345\231\250", nullptr));
        plainTextEdit_2->setPlainText(QCoreApplication::translate("LoginWindow", "\344\275\234\350\200\205\357\274\232\345\260\271\344\273\201\351\276\231\343\200\201\346\270\251\346\265\267\346\264\213\343\200\201\347\224\260\351\223\255\346\235\250", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginWindow", "\350\277\233\345\205\245\347\263\273\347\273\237", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "wuye", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
