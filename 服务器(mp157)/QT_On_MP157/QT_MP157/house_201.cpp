#include "house_201.h"
#include "ui_house_201.h"

House_201::House_201(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::House_201)
{
    ui->setupUi(this);

    QPixmap pm;
    pm.load("./png/house_201.png");
    ui->label->setPixmap(pm);
    ui->label->setScaledContents(true);

    m_pModel = new QStandardItemModel(ui->tableView);//实例化模型，并且指定模型依赖的控件
    //将数据模型设置到表对象上
    ui->tableView->setModel(m_pModel);
    //tableview
    QStringList fonts;
    fonts << "温度" << "湿度" << "光照" << "时间";
    m_pModel->setHorizontalHeaderLabels(fonts);

    pSql = new Sqlite;
    pSql->open_db();
}

House_201::~House_201()
{
    delete ui;
}

void House_201::setComebackWindow(QWidget *pWindow)
{
    this->pComebackWindow = pWindow;
}

//come back
void House_201::on_pushButton_clicked()
{
    this->close();
    pComebackWindow->show();
}

//get data from sql tabel
void House_201::on_pushButton_2_clicked()
{
    //get date from sqlfoem
    QSqlQuery sqlQuery;
    pSql->normalSearch("SELECT * FROM House201 ORDER BY ROWID DESC LIMIT 20",sqlQuery);

    m_pModel->clear();
    while(sqlQuery.next())
    {
        //设置想获取的结果
        QString temp = sqlQuery.value(0).toString();
        QString humi = sqlQuery.value(1).toString();
        QString light = sqlQuery.value(2).toString();
        QString time = sqlQuery.value(3).toString();

        //表单头部
        QStringList fonts;
        fonts << "温度" << "湿度" << "光照" << "时间";
        m_pModel->setHorizontalHeaderLabels(fonts);
        m_pModel->appendRow(QList<QStandardItem *>()<< new QStandardItem(temp)<< new QStandardItem(humi)
                                 << new QStandardItem(light)<< new QStandardItem(time));
     }
}
