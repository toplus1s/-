#ifndef QWDIALOGSIZE_H
#define QWDIALOGSIZE_H

#include<QDialog>
#include<QString>
#include "global.h"

extern class system a;

namespace Ui {
class QWDialogSize;
}

class QWDialogSize : public QDialog
{
    Q_OBJECT
public:
    explicit QWDialogSize(QWidget *parent = 0);
    ~QWDialogSize();
    int status();
    QString id();
    QString name();
    QString sex();
    QString age();
    QString lab();
    QString office();
    QString department();
    QString work();
    QString title();
    QString profession();



    void set(QString status, QString id,QString name,QString sex,QString age,QString profession, QString lab,QString office,QString department,QString work,QString title, int info);

//public slots:
    //void check();

private slots:
    void on_ok_clicked();
    void choose(int index);
    void on_cancel_clicked();
    void on_id_textChanged(const QString &arg1);


private:
    Ui::QWDialogSize *ui;
    int m_info;
    QString m_id;
};
#endif // QWDIALOGSIZE_H
