#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pTcpServer = new QTcpServer(this);
    pTcpServer->listen(QHostAddress::Any,6666);
    pTcpSocket = new QTcpSocket(this);
    connect(pTcpServer,&QTcpServer::newConnection,this,&MainWindow::new_connect_slot);

    pTimer = new QTimer();
    pTimer->start(10000);
    connect(pTimer,&QTimer::timeout,this,&MainWindow::Get_map157_data);

    pSql = new Sqlite;
    pSql->open_db();

    pTcpSetup = new TcpSetup;
    pHouseDate = new HouseData;
    connect(this,&MainWindow::connect_data_toTcpsetWindow,pTcpSetup,&TcpSetup::get_Mainwindow_slot);

    led_status = 0;
    beep_status = 0;
    fan_status = 0;
    motor_status = 4;


    QPixmap pm;
    pm.load("./png/dang_an.png");
    ui->label_3->setPixmap(pm);
    ui->label_3->setScaledContents(true);

    //left
    pm.load("./png/left.png");
    ui->label_7->setPixmap(pm);
    ui->label_7->setScaledContents(true);

    //right
    pm.load("./png/right.png");
    ui->label_6->setPixmap(pm);
    ui->label_6->setScaledContents(true);

    //middle
    pm.load("./png/middle.png");
    ui->label_5->setPixmap(pm);
    ui->label_5->setScaledContents(true);

    pm.load("./png/tcp_logo.png");
    ui->label_4->setPixmap(pm);
    ui->label_4->setScaledContents(true);

    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit_2->setAlignment(Qt::AlignCenter);
    ui->lineEdit_3->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setComebackWindow(QWidget *pWindow)
{
    this->pComebackWindow = pWindow;
}

//when new connection
void MainWindow::new_connect_slot()
{
    pTcpSocket = pTcpServer->nextPendingConnection();
    QString ip = pTcpSocket->peerAddress().toString();
    int port = pTcpSocket->peerPort();
    qDebug()<<QString("%1:%2 connect successed!").arg(ip).arg(port);
    connect(pTcpSocket,&QTcpSocket::readyRead,this,&MainWindow::Socket_readdata);
    connect_data_toTcpsetWindow(port,ip);
}

//LED_ctrl_button
void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"clicked button_led";
    int fd = open("/dev/drv_led0",O_RDWR);
    if(fd < 0)
    {
        qDebug()<<"error";
    }
    if(led_status)
    {
        led_status = 0;
        qDebug()<<"led close";

        ui->pushButton->setStyleSheet(" background-color: rgb(211, 215, 207);font: 20pt ;");
    }
    else
    {
        led_status = 1;
        ui->pushButton->setStyleSheet("background-color: rgb(114, 159, 207);font: 20pt;");
        qDebug()<<"led open";
    }

    write(fd,&led_status,sizeof(led_status));
}

//TCP read data
void MainWindow::Socket_readdata()
{
    QList<int> decimals;
    QByteArray temparr = pTcpSocket->readAll();
    QByteArray temparr_Hex = temparr.toHex();
    // 如果你想要每两个字符之间加上空格或其他分隔符，可以这样做：
    QString hexStringWithSpaces;
    for (int i = 0; i < temparr_Hex.length(); i += 2) {
         hexStringWithSpaces += temparr_Hex.mid(i, 2) + " ";
    }
    //split
   QStringList hexParts = hexStringWithSpaces.split(' ');
   // 遍历每个分割后的16进制字符串
   for (const QString &hexPart : hexParts)
   {
      // 尝试将16进制字符串转换为bool和unsigned int（使用toUInt）
      // 注意：这里使用toUInt(&ok, 16)，其中16是基数，表示我们正在处理16进制数
      bool ok;
      unsigned int decimal = hexPart.toUInt(&ok, 16);
      // 检查转换是否成功
      if (ok)
      {
          // 如果成功，将10进制数添加到列表中
          decimals.append(decimal);
      }
      else
      {
         // 如果失败，可以添加错误处理，这里只是简单地打印一个消息
         qDebug() << "无法将" << hexPart << "转换为10进制数";
      }
   }


    int Check_digit = 0;
    qDebug() << decimals;
    if(decimals[0] == 254)
    {
        Check_digit = decimals[3] + decimals[4] + decimals[5] + decimals[6] + decimals[7] + decimals[8];

        if(Check_digit == decimals[9])
        {
            QString virtual_time = "2024-8-30";
            QDateTime timeData = QDateTime::currentDateTime(); // 获取当前时间
            // 单独获取小时、分钟和秒
            int hours = timeData.time().hour() + 10;
            int minutes = timeData.time().minute();
            int seconds = timeData.time().second();

            // 转换为字符串（可选，如果你想要格式化它们，比如添加前导零）
            QString hoursStr = QString::number(hours, 10).rightJustified(2, '0');
            QString minutesStr = QString::number(minutes, 10).rightJustified(2, '0');
            QString secondsStr = QString::number(seconds, 10).rightJustified(2, '0');
            virtual_time += " " + hoursStr +  ":" + minutesStr + ":" + secondsStr;

            QString temp = QString::number(decimals[3])+"."+QString::number(decimals[4]);
            QString humi = QString::number(decimals[5])+"."+QString::number(decimals[6])+"%";
            if(decimals[8] < 10)
            {
                decimals[8] = decimals[8] *10;
                //QString light = QString::number(decimals[7])+QString::number(decimals[8])+QString::number(0);
            }
            QString light = QString::number(decimals[7])+QString::number(decimals[8]);
            qDebug()<<temp<<" "<<humi<<" "<<light<<" "<<virtual_time;
            //creat sql form
            QString form_name = QString("House%1").arg(decimals[1]);
            if(!pSql->isTableExist(form_name))
            {
                QString sql = QString("CREATE TABLE House%1(Temp TEXT,Humi TEXT,Light TEXT,Time TEXT)")
                                .arg(decimals[1]);
                pSql->normalFunc(sql);
            }
            //insert sql form
            QString sql = QString("INSERT INTO House%1 VALUES('%2','%3','%4','%5')")
                          .arg(decimals[1]).arg(temp).arg(humi).arg(light).arg(virtual_time);
            pSql->normalFunc(sql);

        }
    }
}

//get server's temp and humi in timer
void MainWindow::Get_map157_data()
{
    u16 IIC_data;//读取之后小数在前，整数在后
    double temp;
    double humi;
    int fd = open("/dev/drv_si7006", O_RDWR);
    if(fd < 0)
    {
        qDebug()<<"open drv_si7006 err";
    }

    //IIC读取温湿度
    ioctl(fd,TEMPERARURE,&IIC_data);
    IIC_data = iic_data_change(IIC_data);
    temp = (IIC_data*175.72)/65536 - 46.85;

    //IIC读取温湿度
    ioctl(fd,HUMIDITY,&IIC_data);
    IIC_data = iic_data_change(IIC_data);
    humi = (IIC_data*125)/65536 - 6;
    ui->lineEdit->setText(QString("%1℃").arg(temp));
    ui->lineEdit_2->setText(QString("%1％").arg(humi));
}

//iic_data_change
unsigned short MainWindow::iic_data_change(unsigned short data)
{
    u16  temp_buf;
    temp_buf = data<<8;
    data = (data>>8 | temp_buf);
    return data;
}

//BEEP_ctol_button
void MainWindow::on_pushButton_3_clicked()
{
    qDebug()<<"clicked button_beep";
    int fd = open("/dev/drv_beep",O_RDWR);
    if(fd < 0)
    {
        qDebug()<<"error";
    }
    if(beep_status == 1)
    {
        ui->pushButton_3->setStyleSheet(" background-color: rgb(211, 215, 207);font: 20pt ;");
        beep_status = 2;
        qDebug()<<"beep close";
    }
    else
    {
        ui->pushButton_3->setStyleSheet("background-color: rgb(114, 159, 207);font: 20pt;");
        beep_status = 1;
         qDebug()<<"beep open";
    }
    write(fd,&beep_status,sizeof(beep_status));
}

//FAN_ctol_button
void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"clicked button_fan";
    int fd = open("/dev/drv_fan",O_RDWR);
    if(fd < 0)
    {
        qDebug()<<"error";
    }
    if(fan_status)
    {
        ui->pushButton_2->setStyleSheet(" background-color: rgb(211, 215, 207);font: 20pt ;");
        fan_status = 0;
        qDebug()<<"fan close";
    }
    else
    {
        ui->pushButton_2->setStyleSheet("background-color: rgb(114, 159, 207);font: 20pt;");
        fan_status = 1;
         qDebug()<<"fan open";
    }
    write(fd,&fan_status,sizeof(fan_status));
}

//motor control button
void MainWindow::on_pushButton_4_clicked()
{
    qDebug()<<"clicked motor_led";
    int fd = open("/dev/drv_beep",O_RDWR);
    if(fd < 0)
    {
        qDebug()<<"error";
    }
    if(motor_status == 3)
    {
        ui->pushButton_4->setStyleSheet(" background-color: rgb(211, 215, 207);font: 20pt ;");
        motor_status = 4;
        qDebug()<<"motor close";
    }
    else if(motor_status == 4)
    {
        ui->pushButton_4->setStyleSheet("background-color: rgb(114, 159, 207);font: 20pt;");
        motor_status = 3;
        qDebug()<<"motor open";
    }

    write(fd,&motor_status,sizeof(motor_status));
}


//come back loginWindow
void MainWindow::on_pushButton_9_clicked()
{
    this->close();
    pComebackWindow->show();
}

//go to TCPServer
void MainWindow::on_pushButton_6_clicked()
{
   pTcpSetup->setComebackWindow(this);
   pTcpSetup->show();
   this->hide();
}

//goto houseData Window
void MainWindow::on_pushButton_7_clicked()
{
    pHouseDate->setComebackWindow(this);
    pHouseDate->show();
    this->hide();
}
