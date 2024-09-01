#ifndef HOUSEDATA_H
#define HOUSEDATA_H

#include <QMainWindow>
#include "house_201.h"
namespace Ui {
class HouseData;
}

class HouseData : public QMainWindow
{
    Q_OBJECT

public:
    explicit HouseData(QWidget *parent = nullptr);
    ~HouseData();
    void setComebackWindow(QWidget * pWindow);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::HouseData *ui;
    //指向返回窗口的指针
    QWidget *pComebackWindow;
    House_201 * pHouse_201;
};

#endif // HOUSEDATA_H
