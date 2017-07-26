#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    m_pTableWidget = new FriendManager;

    setCentralWidget(m_pTableWidget);
    setContentsMargins(5 , 10, 5 ,5);

    QPushButton *btnRefresh = new QPushButton;
    btnRefresh->setText(tr("刷新"));

    QPushButton *btnAdd = new QPushButton;
    btnAdd->setText(tr("添加"));

    QPushButton *btnEdit = new QPushButton;
    btnEdit->setText(tr("编辑"));

    QPushButton *btnDel = new QPushButton;
    btnDel->setText(tr("删除"));

    QWidget *widget = new QWidget;
    widget->setMinimumSize(20 ,55);
    widget->setContentsMargins(0,0,0,10);

    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    hLayout->addWidget(btnRefresh);
    hLayout->addWidget(btnAdd);
    hLayout->addWidget(btnEdit);
    hLayout->addWidget(btnDel);

    widget->setLayout(hLayout);
    ui->menuBar->setCornerWidget(widget ,Qt::TopRightCorner);

    connect(btnRefresh , SIGNAL(clicked(bool)) , this ,SLOT(onBtnRefresh()));
    connect(btnAdd , SIGNAL(clicked(bool)) , this ,SLOT(onBtnAdd()));
    connect(btnEdit , SIGNAL(clicked(bool)), this ,SLOT(onBtnEdit()));
    connect(btnDel , SIGNAL(clicked(bool)) ,this , SLOT(onBtnDel()));
}

void MainWindow::onBtnRefresh()
{
    qDebug()<<"onBtnRefresh";
    QList<QStringList> tableData;

//    tableData = m_pCreateDb->selectDataFromBase();
//    if(!tableData.isEmpty())
//    {
//        m_pTableWidget->clearTableData();
//        QListIterator<QStringList> itr(tableData);
//        while(itr.hasNext())
//        {
//            m_pTableWidget->appendRowData(itr.next());
//        }
//    }
}

void MainWindow::onBtnAdd()
{
    qDebug()<<"onBtnAdd";
//    m_operateType = Add;
//    if(m_pAddStuDlg)
//    {
//        m_pAddStuDlg->activateWindow();
//        m_pAddStuDlg->setWindowTitle(tr("添加: 学生信息"));
//        m_pAddStuDlg->exec();
//    }
}

void MainWindow::onBtnEdit()
{
    qDebug()<<"onBtnEdit";

//    m_operateType = Edit;

//    QStringList rowData ;
//    rowData = m_pTableWidget->getCurrentRowData();
//    if(rowData.isEmpty())
//    {
//        QMessageBox::information(this, tr("提示") , tr("请选中需要编辑的数据!"));
//        return ;
//    }
//    else
//    {
//        m_pAddStuDlg->setEditData(rowData);
//    }

//    m_pAddStuDlg->activateWindow();
//    m_pAddStuDlg->setWindowTitle(tr("修改: 学生信息"));
//    m_pAddStuDlg->exec();
}

void MainWindow::onBtnDel()
{
    qDebug()<<"onBtnDel";
//    QString ID = m_pTableWidget->getCurrentPhone();
//    if(ID.isEmpty())
//    {
//        QMessageBox::information(this , tr("提示") , tr("请选中一条记录！"));
//        return ;
//    }

//    QMessageBox::StandardButton button = QMessageBox::question(this , tr("提示") ,tr("确定删除这一条记录？"));
//    if(button == QMessageBox::Yes)
//    {
//        //删除操作
//        ExecDelSql(ID);
//    }
}
