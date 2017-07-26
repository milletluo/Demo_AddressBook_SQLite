#ifndef FRIENDMANAGER_H
#define FRIENDMANAGER_H

#include <QWidget>

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
private:
    Ui::FriendManager *ui;
};

#endif // FRIENDMANAGER_H
