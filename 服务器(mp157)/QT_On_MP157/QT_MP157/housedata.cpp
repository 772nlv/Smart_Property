#include "housedata.h"
#include "ui_housedata.h"

HouseData::HouseData(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HouseData)
{
    ui->setupUi(this);
    QPixmap pm;
    pm.load("./png/HOUSE_CASE.png");
    ui->label->setPixmap(pm);
    ui->label->setScaledContents(true);

    pm.load("./png/right_up.png");
    ui->label_2->setPixmap(pm);
    ui->label_2->setScaledContents(true);

    pHouse_201 = new House_201;
}

HouseData::~HouseData()
{
    delete ui;
}

void HouseData::setComebackWindow(QWidget *pWindow)
{
    this->pComebackWindow = pWindow;
}

void HouseData::on_pushButton_clicked()
{
    this->close();
    pComebackWindow->show();
}

//enter House201 window
void HouseData::on_pushButton_2_clicked()
{
    pHouse_201->setComebackWindow(this);
    pHouse_201->show();
    this->hide();
}
