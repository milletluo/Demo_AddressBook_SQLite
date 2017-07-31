#ifndef FRIENDMANAGER_H
#define FRIENDMANAGER_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class FriendManager;
}

class FriendManager : public QWidget
{
    Q_OBJECT

public:
    explicit FriendManager(QWidget *parent = 0);
    ~FriendManager();

    void appendRowData(QStringList rowData); //添加一行数据
    void clearTableData(); //清除表格数据
    QStringList getCurrentRowData();
    QString getCurrentPhone();

    void setTableModel(QSqlTableModel* model); //建立了数据库和QTableview的映射
public:
    Ui::FriendManager *ui;
};

#endif // FRIENDMANAGER_H
