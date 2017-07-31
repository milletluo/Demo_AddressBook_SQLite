#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUi();
    initDB();  //打开数据库
    onBtnRefresh(); //程序启动时，查询数据
    m_operateType = Add;
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
    btnRefresh->setText(QStringLiteral("刷新"));

    QPushButton *btnAdd = new QPushButton;
    btnAdd->setText(QStringLiteral("添加"));

    QPushButton *btnEdit = new QPushButton;
    btnEdit->setText(QStringLiteral("编辑"));

    QPushButton *btnDel = new QPushButton;
    btnDel->setText(QStringLiteral("删除"));

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

    m_pAddStuDlg = new AddStuDlg;
    connect(m_pAddStuDlg , SIGNAL(signalStuInfo(QVariantMap)) , this ,SLOT(ExecAddSql(QVariantMap)));
    connect(m_pAddStuDlg , SIGNAL(signalStuInfo(QVariantMap)) , this ,SLOT(ExecEditSql(QVariantMap)));

}

void MainWindow::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("localhost");//设置主机名
    db.setDatabaseName("AddressBook.db");
    //db.setUserName("root");   // 如果是 SQLite 不需要
    //db.setPassword("root");   // 如果是 SQLite 不需要
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"Create DB";

        QSqlQuery query;
        query.exec("create table FriendManager (create_date datetime, "
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(20) ,phone varchar(20), "
                   "email varchar(20) , address varchar(20) , description varchar(50))");
    }
    else
    {
        qDebug()<<"open failed"<<db.databaseName();
    }
}

QList<QStringList> MainWindow::selectDataFromBase()
{
    QSqlQuery query("SELECT * FROM FriendManager");

    QList<QStringList> stuInfo;

    while (query.next())
    {
        QStringList rowData ;

        rowData <<query.value(2).toString();
        rowData <<query.value(3).toString();
        rowData <<query.value(4).toString();
        rowData <<query.value(5).toString();
        rowData <<query.value(6).toString();
        rowData <<query.value(7).toString();

        stuInfo.append(rowData);
    }
    return stuInfo;
}

void MainWindow::onBtnRefresh()
{
    qDebug()<<"onBtnRefresh";
    QList<QStringList> tableData;

    tableData = selectDataFromBase();
    if(!tableData.isEmpty())
    {
        m_pTableWidget->clearTableData();
        QListIterator<QStringList> itr(tableData);
        while(itr.hasNext())
        {
            m_pTableWidget->appendRowData(itr.next());
        }
    }

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("FriendManager");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    m_pTableWidget->setTableModel(model);
}

void MainWindow::onBtnAdd()
{
    qDebug()<<"onBtnAdd";
    m_operateType = Add;

    if(m_pAddStuDlg)
    {
        m_pAddStuDlg->activateWindow();
        m_pAddStuDlg->setWindowTitle(QStringLiteral("添加联系人"));
        m_pAddStuDlg->exec();
    }
}

void MainWindow::onBtnEdit()
{
    qDebug()<<"onBtnEdit";
    m_operateType = Edit;

    QStringList rowData ;
    rowData = m_pTableWidget->getCurrentRowData();
    if(rowData.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提示") , QStringLiteral("请选中需要编辑的数据!"));
        return ;
    }
    else
    {
        m_pAddStuDlg->setEditData(rowData);
    }

    m_pAddStuDlg->activateWindow();
    m_pAddStuDlg->setWindowTitle(QStringLiteral("修改联系人"));
    m_pAddStuDlg->exec();
}

void MainWindow::onBtnDel()
{
    qDebug()<<"onBtnDel";
    QString Phone = m_pTableWidget->getCurrentPhone();
    if(Phone.isEmpty())
    {
        QMessageBox::information(this , QStringLiteral("提示") , QStringLiteral("请选中一条记录！"));
        return ;
    }

    QMessageBox::StandardButton button = QMessageBox::question(this , QStringLiteral("提示") ,QStringLiteral("确定删除这一条记录？"));
    if(button == QMessageBox::Yes)
    {
        //删除操作
        ExecDelSql(Phone);
    }
}

void MainWindow::ExecAddSql(QVariantMap stuInfo)
{
    if(m_operateType == Add)
    {
        QString create_date = stuInfo.value("datetime").toString();
        QString phone = stuInfo.value("phone").toString();
        QString name = stuInfo.value("name").toString();
        QString email = stuInfo.value("email").toString();
        QString address = stuInfo.value("address").toString();
        QString description = stuInfo.value("desc").toString();

        QString sql;
        sql = QString("insert into FriendManager (create_date,name ,phone ,email ,address , description)"
                      " VALUES ('%1', '%2' , '%3' , '%4' , '%5' , '%6')")
                .arg(create_date).arg(name).arg(phone).arg(email).arg(address).arg(description);

        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
            QStringList rowData;
            rowData << name <<phone <<email << address << description ;
            m_pTableWidget->appendRowData(rowData);
            onBtnRefresh(); //重新加载数据
            QMessageBox::information(this ,QStringLiteral("提示") , QStringLiteral("添加成功!"));
        }
        else
        {
            QMessageBox::information(this ,QStringLiteral("提示") , QStringLiteral("添加失败!"));
        }
    }
}

void MainWindow::ExecEditSql(QVariantMap stuInfo)
{
    if(m_operateType == Edit)
    {
        QString create_date = stuInfo.value("datetime").toString();
        QString phone = stuInfo.value("phone").toString();
        QString name = stuInfo.value("name").toString();
        QString email = stuInfo.value("email").toString();
        QString address = stuInfo.value("address").toString();
        QString description = stuInfo.value("desc").toString();

        QString sql;
        sql = QString("UPDATE FriendManager "
                      "set create_date = '%0' ,name = '%1' ,phone = '%2',"
                      "email = '%3', address = '%4',description = '%5'"
                      " where phone = '%6' ")
                .arg(create_date).arg(name).arg(phone).arg(email).arg(address).arg(description).arg(phone);

        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {
            onBtnRefresh(); //重新加载数据
            QMessageBox::information(this ,QStringLiteral("提示") , QStringLiteral("修改成功!"));
        }
        else
        {
            QMessageBox::information(this ,QStringLiteral("提示") , QStringLiteral("修改失败!"));
        }
    }
}

void MainWindow::ExecDelSql(QString phone)
{
    QString sql;
    sql = QString("DELETE FROM FriendManager "
                  " where phone = '%1' ").arg(phone);

    QSqlQuery query;
    bool ok = query.exec(sql);
    if(ok)
    {
        onBtnRefresh(); //重新加载数据
        QMessageBox::information(this ,QStringLiteral("提示") , QStringLiteral("删除成功!"));
    }
    else
    {
        QMessageBox::information(this ,QStringLiteral("提示") , QStringLiteral("删除失败!"));
    }
}
