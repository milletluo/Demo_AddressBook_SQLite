#ifndef ADDSTUDLG_H
#define ADDSTUDLG_H

#include <QDialog>
#include <QVariantMap>

namespace Ui {
class AddStuDlg;
}

class AddStuDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddStuDlg(QWidget *parent = 0);
    ~AddStuDlg();

    void setEditData(QStringList rowData);

signals:
    void signalStuInfo(QVariantMap stuInfo);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::AddStuDlg *ui;

    void clearData();
    void closeEvent(QCloseEvent *event);
};

#endif // ADDSTUDLG_H
