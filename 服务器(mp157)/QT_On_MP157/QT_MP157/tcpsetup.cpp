#include "tcpsetup.h"
#include "ui_tcpsetup.h"
#include "mainwindow.h"
TcpSetup::TcpSetup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpSetup)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit_2->setAlignment(Qt::AlignCenter);
    ui->textEdit->setText("TCP server is openned!!\r\n");
}

TcpSetup::~TcpSetup()
{
    delete ui;
}

void TcpSetup::setComebackWindow(QWidget *pWindow)
{
    this->pComebackWindow = pWindow;
}
//come back
void TcpSetup::on_pushButton_clicked()
{
    this->close();
    pComebackWindow->show();
}

//get Mainwindow's connected data
void TcpSetup::get_Mainwindow_slot(int number, QString text)
{
   QString initial_str = ui->textEdit->toPlainText();
   QString temparr =  QString("%1:%2 connect successed!\r\n").arg(text).arg(number);
   initial_str += temparr;
   ui->textEdit->setText(initial_str);
}


//server ctrl_button
void TcpSetup::on_pushButton_3_clicked()
{
    if(ui->pushButton_3->text() == QString("Close_Server"))
    {
        ui->pushButton_3->setText("Open_Server");
        QString initial_str = ui->textEdit->toPlainText();
        QString temparr =  QString("Tcp Server is closed\r\n");
        initial_str += temparr;
        ui->textEdit->setText(initial_str);
    }
    else
    {
        ui->pushButton_3->setText("Close_Server");
        QString initial_str = ui->textEdit->toPlainText();
        QString temparr =  QString("Tcp Server is openned\r\n");
        initial_str += temparr;
        ui->textEdit->setText(initial_str);
    }
}

//clean textEdits
void TcpSetup::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
}
