#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "friendmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onBtnAdd();
    void onBtnEdit();
    void onBtnDel();
    void onBtnRefresh();

//    void ExecAddSql(QVariantMap stuInfo);
//    void ExecEditSql(QVariantMap stuInfo);
//    void ExecDelSql(QString id);

private:
    Ui::MainWindow *ui;
    FriendManager *m_pTableWidget;

    void initUi();
};

#endif // MAINWINDOW_H
