#ifndef TCPSETUP_H
#define TCPSETUP_H

#include <QMainWindow>

namespace Ui {
class TcpSetup;
}

class TcpSetup : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpSetup(QWidget *parent = nullptr);
    ~TcpSetup();
    void setComebackWindow(QWidget * pWindow);
    void get_Mainwindow_slot(int number, QString text);
private slots:
    void on_pushButton_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TcpSetup *ui;
    //指向返回窗口的指针
    QWidget *pComebackWindow;
};

#endif // TCPSETUP_H
