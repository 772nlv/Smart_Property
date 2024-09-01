#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QPixmap pm;
    pm.load("./png/fs_logo_1.png");
    //按比例设置图片
    ui->label->setPixmap(pm);
    ui->label->setScaledContents(true);
    pm.load("./png/wuye.png");

    //按比例设置图片
    ui->label_2->setPixmap(pm);
    ui->label_2->setScaledContents(true);
    pMainwindow = new MainWindow;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

//enter system
void LoginWindow::on_pushButton_clicked()
{
    pMainwindow->setComebackWindow(this);
    pMainwindow->show();
    this->hide();
}
