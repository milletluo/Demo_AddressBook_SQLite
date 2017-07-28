#include "addstudlg.h"
#include "ui_addstudlg.h"
#include <QDateTime>
#include <QString>

AddStuDlg::AddStuDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStuDlg)
{
    ui->setupUi(this);
    setFixedSize(sizeHint());
}

AddStuDlg::~AddStuDlg()
{
    delete ui;
}

void AddStuDlg::setEditData(QStringList rowData)
{
    ui->NameEdit->setText(rowData.at(0));
    ui->PhoneEdit->setText(rowData.at(1));
    ui->EmailEdit->setText(rowData.at(2));
    ui->AddressEdit->setText(rowData.at(3));
    ui->DescText->setText(rowData.at(4));

    //ui->PhoneEdit->setEnabled(false);
}

void AddStuDlg::clearData()
{
    ui->NameEdit->clear();
    ui->PhoneEdit->clear();
    ui->EmailEdit->clear();
    ui->AddressEdit->clear();
    ui->DescText->clear();
}

void AddStuDlg::closeEvent(QCloseEvent *event)
{
    clearData();
}

void AddStuDlg::on_buttonBox_accepted()
{
    QVariantMap stuInfo;

    QString name = ui->NameEdit->text();
    QString phone = ui->PhoneEdit->text();
    QString email = ui->EmailEdit->text();
    QString address = ui->AddressEdit->text();
    QString desc = ui->DescText->toPlainText();

    QString datetime = QDateTime::currentDateTime().toString();

    stuInfo.insert("datetime" ,datetime );
    stuInfo.insert("name" ,name );
    stuInfo.insert("phone" ,phone );
    stuInfo.insert("email" ,email );
    stuInfo.insert("address" ,address );
    stuInfo.insert("desc" ,desc );

    emit signalStuInfo(stuInfo);
    //ui->PhoneEdit->setEnabled(true);
}

void AddStuDlg::on_buttonBox_rejected()
{
    //ui->PhoneEdit->setEnabled(true);
    close();
}
