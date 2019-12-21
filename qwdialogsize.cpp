#include "qwdialogsize.h"
#include "ui_qwdialogsize.h"
#include<QMessageBox>
#include<qdebug.h>

QWDialogSize::QWDialogSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogSize)
{
    ui->setupUi(this);
    ui->info->hide();
    connect(ui->status,SIGNAL(currentIndexChanged(int)),this,SLOT(choose(int)));
}

QWDialogSize::~QWDialogSize()
{
    delete ui;
}


int QWDialogSize::status()
{
    return ui->status->currentIndex();
}

QString QWDialogSize::id()
{
    return ui->id->text();
}

QString QWDialogSize::name()
{
    return ui->name->text();
}

QString QWDialogSize::sex()
{
    int i = ui->sex->currentIndex();
    if(i==0)
        return "男";
    else
        return "女";
}

QString QWDialogSize::age()
{
    int i = ui->age->value();
    return QString::number(i);
}

QString QWDialogSize::office()
{
    return ui->office->text();
}

QString QWDialogSize::lab()
{
    return ui->lab->text();
}

QString QWDialogSize::work()
{
    return ui->work->text();
}


QString QWDialogSize::title()
{
    return ui->title->text();
}

QString QWDialogSize::department()
{
    return ui->department->text();
}

QString QWDialogSize::profession()
{
    return ui->profession->text();
}



void QWDialogSize::choose(int index)
{
    if(index==0)
    {
         ui->office->setEnabled(0);
         ui->work->setEnabled(0);
         ui->lab->setEnabled(0);
         ui->department->setEnabled(1);
         ui->profession->setEnabled(1);
         ui->title->setEnabled(1);
    }
    else if(index==1)
    {
        ui->department->setEnabled(0);
        ui->profession->setEnabled(0);
        ui->title->setEnabled(0);
        ui->office->setEnabled(0);
        ui->work->setEnabled(1);
        ui->lab->setEnabled(1);
    }
    else if(index==2)
    {
        ui->department->setEnabled(0);
        ui->profession->setEnabled(0);
        ui->title->setEnabled(0);
        ui->lab->setEnabled(0);
        ui->office->setEnabled(1);
        ui->work->setEnabled(1);
    }
    else if(index==3)
    {
        ui->office->setEnabled(1);
        ui->work->setEnabled(1);
        ui->department->setEnabled(1);
        ui->profession->setEnabled(1);
        ui->title->setEnabled(1);
        ui->lab->setEnabled(0);
    }
}


void QWDialogSize::set(QString status, QString id,QString name,QString sex,QString age,QString profession,QString lab,QString office,QString department,QString work,QString title, int info)
{
    m_info = info;
    m_id = id;
    if(info == 1)
        ui->status->setEnabled(1);
    else
        ui->status->setEnabled(0);
    if(status == "教师信息")
        ui->status->setCurrentIndex(0);
    else if(status == "实验员信息")
        ui->status->setCurrentIndex(1);
    else if(status == "行政人员信息")
        ui->status->setCurrentIndex(2);
    else
        ui->status->setCurrentIndex(3);
    ui->id->setText(id);
    ui->name->setText(name);
    if(sex=="男")
        ui->sex->setCurrentIndex(0);
    else
        ui->sex->setCurrentIndex(1);
    ui->age->setValue(age.toInt());
    if(office == "缺省")
    {
        ui->office->setText("");
        ui->office->setEnabled(0);
    }
    else
        ui->office->setText(office);
    if(department == "缺省")
    {
        ui->department->setText("");
        ui->department->setEnabled(0);
    }
    else
        ui->department ->setText(department);
    if(title == "缺省")
    {
        ui->title->setText("");
        ui->title->setEnabled(0);
    }
    else
        ui->title->setText(title);
    if(work == "缺省")
    {
        ui->work->setText("");
        ui->work->setEnabled(0);
    }
    else
        ui->work->setText(work);
    if(lab == "缺省")
    {
        ui->lab->setText("");
        ui->lab->setEnabled(0);
    }
    else
        ui->lab->setText(lab);
    if(profession == "缺省")
    {
        ui->profession->setText("");
        ui->profession->setEnabled(0);
    }
    else
        ui->profession->setText(profession);


}

void QWDialogSize::on_ok_clicked()
{
    accept();
}

void QWDialogSize::on_cancel_clicked()
{
    reject();
}

void QWDialogSize::on_id_textChanged(const QString &arg1)
{
    if(m_info == 1)
    {
        if(!a.search(arg1))
        {
            ui->info->show();
            ui->ok->setEnabled(0);
        }
        else
        {
            ui->info->hide();
            ui->ok->setEnabled(1);
        }
    }
    else
    {
        if(!a.search2(arg1, m_id))
        {
            ui->info->show();
            ui->ok->setEnabled(0);
        }
        else
        {
            ui->info->hide();
            ui->ok->setEnabled(1);
        }
    }
}


