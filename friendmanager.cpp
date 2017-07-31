#include "friendmanager.h"
#include "ui_friendmanager.h"
#include <QTableWidgetItem>
#include <QHeaderView>

FriendManager::FriendManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendManager)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() <<QStringLiteral("姓名") << QStringLiteral("电话")<< QStringLiteral("邮箱")
                                               <<QStringLiteral("家庭住址") <<QStringLiteral("描述"));

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

FriendManager::~FriendManager()
{
    delete ui;
}

void FriendManager::appendRowData(QStringList rowData)
{
    int row = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row);

    for(int i  = 0 ; i < rowData.size() ; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(rowData.at(i));
        ui->tableWidget->setItem(row , i , item);
    }
}

void FriendManager::clearTableData()
{
    //清除表格
    int rowCount = ui->tableWidget->rowCount();
    for(int r = rowCount-1 ; r >=0 ; r--)
    {
        ui->tableWidget->removeRow(r);
    }
}

QStringList FriendManager::getCurrentRowData()
{
    QStringList rowData;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        rowData << ui->tableWidget->item(row , 0)->text();
        rowData << ui->tableWidget->item(row , 1)->text();
        rowData << ui->tableWidget->item(row , 2)->text();
        rowData << ui->tableWidget->item(row , 3)->text();
        rowData << ui->tableWidget->item(row , 4)->text();
    }
    return rowData;
}

QString FriendManager::getCurrentPhone()
{
    QString Phone ;
    int row = ui->tableWidget->currentRow();
    if(row != -1)
    {
        Phone =  ui->tableWidget->item(row , 1)->text();
    }
    return Phone;
}

void FriendManager::setTableModel(QSqlTableModel* model)
{
    //建立数据库和QTableview的映射
    ui->tableView->setModel(model);
    ui->tableView->show();
}
