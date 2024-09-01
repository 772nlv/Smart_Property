#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include "sqlite.h"
#include "tcpsetup.h"
#include "housedata.h"
#include <QDateTime>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define TEMPERARURE _IOR('T', 0x01, unsigned short)
#define HUMIDITY _IOR('H', 0x02, unsigned short)
#define u16 unsigned short
class MainWindow : public QMainWindow
{
    Q_OBJECT//get data from sqlform

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setComebackWindow(QWidget * pWindow);
signals:
    void connect_data_toTcpsetWindow(int number, QString text);
private slots:
    //有新的连接时，槽函数
    void new_connect_slot();

    //LED_ctrl_button
    void on_pushButton_clicked();

    //TCP read data
    void Socket_readdata();

    //get server's temp and humi in timer
    void Get_map157_data();

    //iic_data_change
    u16 iic_data_change(u16 data);

    //BEEP_ctrl_button
    void on_pushButton_3_clicked();

    //FAN_ctol_button
    void on_pushButton_2_clicked();

    //motor control button
    void on_pushButton_4_clicked();

    //come back loginWindow
    void on_pushButton_9_clicked();

    //go to TCPServer Window
    void on_pushButton_6_clicked();
    
    //goto houseData Window
    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer * pTcpServer;
    QTcpSocket * pTcpSocket;
    int led_status;//
    int beep_status;//
    int fan_status;//
    int motor_status;//
    QTimer * pTimer;//timer
    Sqlite *pSql;//sql
    //指向返回窗口的指针
    QWidget *pComebackWindow;//last Window

    TcpSetup *pTcpSetup; //Tcpsetup Window
    HouseData *pHouseDate;//House Data window

};
#endif // MAINWINDOW_H














