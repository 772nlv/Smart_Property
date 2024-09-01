#ifndef HOUSE_201_H
#define HOUSE_201_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "sqlite.h"
namespace Ui {
class House_201;
}

class House_201 : public QMainWindow
{
    Q_OBJECT

public:
    explicit House_201(QWidget *parent = nullptr);
    ~House_201();
    void setComebackWindow(QWidget * pWindow);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::House_201 *ui;
    //指向返回窗口的指针
    QWidget *pComebackWindow;
    //数据模型 导入tableview
    QStandardItemModel *m_pModel;
    Sqlite *pSql;
};

#endif // HOUSE_201_H
