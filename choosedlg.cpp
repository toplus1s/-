#include "choosedlg.h"
#include "ui_choosedlg.h"

choosedlg::choosedlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choosedlg)
{
    ui->setupUi(this);
}

choosedlg::~choosedlg()
{
    delete ui;
}

cho choosedlg::ifchosed()
{
    cho res;
    if(ui->all->isChecked())
        res.allc = 1;
    else
        res.allc = 0;
    if(ui->teachaer->isChecked())
        res.teac = 1;
    else
        res.teac = 0;
    if(ui->assistant->isChecked())
        res.assc = 1;
    else
        res.assc = 0;
    if(ui->staff->isChecked())
        res.stac = 1;
    else
        res.stac = 0;
    if(ui->tstaff->isChecked())
        res.tstc = 1;
    else
        res.tstc = 0;
    if(ui->male->isChecked())
        res.malc = 10;
    else
        res.malc = 1;
    if(ui->female->isChecked())
        res.femc = 20;
    else
        res.femc = 5;
    return res;
}


void choosedlg::on_ok_clicked()
{
    accept();
}

void choosedlg::on_cancel_clicked()
{
    reject();
}
