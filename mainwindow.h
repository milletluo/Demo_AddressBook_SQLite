#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "friendmanager.h"
#include "addstudlg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum OperateType
    {
        Add ,
        Edit
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onBtnAdd();
    void onBtnEdit();
    void onBtnDel();
    void onBtnRefresh();
    void onBtnSelect();

    void ExecAddSql(QVariantMap stuInfo);
    void ExecEditSql(QVariantMap stuInfo);
    void ExecDelSql(QString phone);

private:
    Ui::MainWindow *ui;

    OperateType m_operateType;
    FriendManager *m_pTableWidget;
    AddStuDlg* m_pAddStuDlg;
    QLineEdit *ledSelect;
    QWidget *widget;

    void initUi();
    void initDB();
    QList<QStringList> selectDataFromBase();
};

#endif // MAINWINDOW_H
