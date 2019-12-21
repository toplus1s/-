#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<windows.h>
#include<qdebug.h>
#include<QFileDialog>
#include<string>
#include<QTimer>
#include<QInputDialog>
#include<QMessageBox>
#include<QScrollBar>
#include<QCheckBox>
#include "choosedlg.h"
#include <QDesktopServices>
#include <QUrl>

#pragma execution_character_set("utf-8")
using namespace std;

myCommand::myCommand(QString str, QString id, bool oldT, bool newT)
{
              m_str = str;
              m_id = id;
              m_oldT = oldT;
              m_newT = newT;

        }

void myCommand::redo()
{
    if(m_str == "add")
        a.recycle(m_id);
    else if(m_str == "del")
        a.del(m_id.toStdString());
    else
        a.restore(m_id, m_str);
}

void myCommand::undo()
{
    if(m_str == "add")
        a.del(m_id.toStdString());
    else if(m_str == "del")
        a.recycle(m_id);
    else
        a.restore(m_str, m_id);


}




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowIcon(QIcon("../icon/myicon.ico"));
    this->setWindowTitle("高校人员信息管理系统");
    ui->txt->setStyleSheet("QTextEdit{border-width:0;border-style:outset}");
    ui->txt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->txt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->txt->verticalScrollBar()->setValue(ui->txt->verticalScrollBar()->maximumHeight());
    ui->txt->setLineWrapMode(QTextEdit::NoWrap);
    ui->save->setEnabled(0);
    ui->save_ano->setEnabled(0);
    ui->close->setEnabled(0);
    ui->export_2->setEnabled(0);
    m_UndoStack = new QUndoStack(this);
    QAction *undoAction = m_UndoStack->createUndoAction(this);
    QAction *redoAction = m_UndoStack->createRedoAction(this);
    undoAction->setIcon(QIcon("../icon/undo.ico")); //选两张撤销 前进的icon图片
    redoAction->setIcon(QIcon("../icon/redo.ico"));
    ui->menu_E->insertAction(ui->menu_E->actions().value(ui->menu_E->actions().size()), undoAction);
    ui->menu_E->insertAction(undoAction, redoAction);
    ui->menu_E->insertSeparator(redoAction);
    undoAction->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));
    redoAction->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Y));
    connect(undoAction,SIGNAL(triggered()),this,SLOT(refresh()));
    connect(redoAction,SIGNAL(triggered()),this,SLOT(refresh()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_new_2_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存"),"D:",tr("信息管理系统文件(*.ims)"));
    string s = fileName.toStdString();
    a.save(s);
    ui->save->setEnabled(1);
    ui->save_ano->setEnabled(1);
    ui->close->setEnabled(1);
    ui->export_2->setEnabled(1);
}




void MainWindow::on_open_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this,tr("打开"),"D:",tr("信息管理系统文件(*.ims);;""文本文档(*.txt)"));
    filepath= fileName.toStdString();
    if(filepath!="")
    {
        if(a.open(filepath))
        {
            ui->txt->document()->clear();
            ui->txt->insertPlainText(a.output1(1,0));
            ui->txt->insertPlainText(a.output2(1,0));
            ui->txt->insertPlainText(a.output3(1,0));
            ui->txt->insertPlainText(a.output4(1,0));
            ui->save->setEnabled(1);
            ui->save_ano->setEnabled(1);
            ui->close->setEnabled(1);
            ui->export_2->setEnabled(1);
        }
        else
        {
            QString text = QInputDialog::getText(this, tr("保护文档"), tr("password:"));
            extern QString password;
            if(text == password)
            {
                a.openff(filepath);
                ui->txt->document()->clear();
                ui->txt->insertPlainText(a.output1(1,0));
                ui->txt->insertPlainText(a.output2(1,0));
                ui->txt->insertPlainText(a.output3(1,0));
                ui->txt->insertPlainText(a.output4(1,0));
                ui->save->setEnabled(1);
                ui->save_ano->setEnabled(1);
                ui->close->setEnabled(1);
                ui->export_2->setEnabled(1);
            }
            else
                showWarningDlg("密码不正确！");
        }

    }
}




void MainWindow::on_save_triggered()
{
    a.save(filepath);
}




void MainWindow::on_save_ano_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("另存为"),"D:",tr("信息管理系统文件(*.ims)"));
    string s = fileName.toStdString();
    a.save(s);
}





void MainWindow::on_export_2_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("导出为"),"D:",tr("word文档(*.doc);;""文本文档(*.txt)"));
    string s = fileName.toStdString();
    a.exportf(s);
}




void MainWindow::on_close_triggered()
{
    ui->txt->document()->clear();
}




void MainWindow::on_quit_triggered()
{
    qApp->quit();
}





void MainWindow::on_del_triggered()
{
    extern int jilu;
    jilu = 0;
    QString text = QInputDialog::getText(this, tr("删除"), tr("ID/姓名:"));
    QString ss =  a.find(text);
    if(jilu > 1)
    {
        QString message = "共找到"+QString::number(jilu)+"条记录\n\n";
        showInfoDlg(message+ss);
        on_del_triggered();
    }
    else if(jilu == 1)
    {
        string s = text.toStdString();
        if(a.del(s))
        {
            showInfoDlg("删除成功\n");
            m_UndoStack->push(new myCommand("del",text,0,1));
            ui->txt->document()->clear();
            ui->txt->insertPlainText(a.output1(1,0));
            ui->txt->insertPlainText(a.output2(1,0));
            ui->txt->insertPlainText(a.output3(1,0));
            ui->txt->insertPlainText(a.output4(1,0));
        }
    }
    else
        showWarningDlg("输入信息不正确，未找到与搜索条件匹配的内容\n");
    jilu = 0;
}





void MainWindow::on_find_triggered()
{
    QString text = QInputDialog::getText(this, tr("查找"), tr("ID/姓名:"));
    QString s =  a.find(text);
    extern int jilu;
    QString message = "共找到"+QString::number(jilu)+"条记录\n\n";
    showInfoDlg(message+s);
    jilu = 0;
}




void MainWindow::on_add_triggered()
{
    QWDialogSize *dlgInfo=new QWDialogSize(this);
    Qt::WindowFlags flags=dlgInfo->windowFlags();
    dlgInfo->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dlgInfo->set("教师信息", "", "", "男", "","", "缺省","缺省", "", "缺省", "", 1);
    int ret = dlgInfo->exec();
    if (ret == QDialog::Accepted)
    {
        qDebug()<<a.search(dlgInfo->id());
            setinit s;
            s.id=dlgInfo->id();
            s.name=dlgInfo->name();
            s.sex=dlgInfo->sex();
            s.age=dlgInfo->age();
            s.profession=dlgInfo->profession();
            s.office=dlgInfo->office();
            s.department=dlgInfo->department();
            s.title=dlgInfo->title();
            s.work=dlgInfo->work();
            s.lab=dlgInfo->lab();
            a.input(dlgInfo->status(), s);
            showInfoDlg("添加成功\n");
            m_UndoStack->push(new myCommand("add",s.id,0,1));
            ui->txt->document()->clear();
            ui->txt->insertPlainText(a.output1(1,0));
            ui->txt->insertPlainText(a.output2(1,0));
            ui->txt->insertPlainText(a.output3(1,0));
            ui->txt->insertPlainText(a.output4(1,0));
    }
    delete dlgInfo;
}





void MainWindow::on_edit_triggered()
{
    extern int jilu;
    jilu = 0;
    QString text = QInputDialog::getText(this, tr("查找"), tr("ID/姓名:"));
    QString s =  a.find(text);

    if(jilu > 1)
    {
        QString message = "共找到"+QString::number(jilu)+"条记录\n\n";
        showInfoDlg(message+s);
        on_edit_triggered();
    }
    else if(jilu == 1)
    {
        setinit ss = a.edit(text);
        QWDialogSize *dlgInfo=new QWDialogSize(this);
        Qt::WindowFlags flags=dlgInfo->windowFlags();
        dlgInfo->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
        dlgInfo->set(ss.status, ss.id, ss.name, ss.sex, ss.age, ss.profession, ss.lab, ss.office, ss.department, ss.work, ss.title, 0);
        int ret = dlgInfo->exec();
        if (ret == QDialog::Accepted)
        {
            setinit s;
            s.id=dlgInfo->id();
            s.name=dlgInfo->name();
            s.sex=dlgInfo->sex();
            s.age=dlgInfo->age();
            s.profession=dlgInfo->profession();
            s.office=dlgInfo->office();
            s.department=dlgInfo->department();
            s.title=dlgInfo->title();
            s.work=dlgInfo->work();
            s.lab=dlgInfo->lab();
            s.intst = dlgInfo->status();
            a.input(ss.id.toStdString(), s);
            showInfoDlg("修改成功\n");
            m_UndoStack->push(new myCommand(s.id, ss.id,0,1));
            ui->txt->document()->clear();
            ui->txt->insertPlainText(a.output1(1,0));
            ui->txt->insertPlainText(a.output2(1,0));
            ui->txt->insertPlainText(a.output3(1,0));
            ui->txt->insertPlainText(a.output4(1,0));
        }
        delete dlgInfo;
    }
    else
        showWarningDlg("输入信息不正确，未找到与搜索条件匹配的内容\n");
}





void MainWindow::on_addup_triggered()
{
    cal sum = a.calc();
    QString s ="教师总人数为："+ QString::number(sum.tean)+"\n实验员总人数为："+ QString::number(sum.assn)+"\n行政人员总人数为："+ QString::number(sum.stan)+"\n教师兼行政人员总人数为："+QString::number(sum.tstn)+"\n总人数为："+QString::number(sum.alln)+"\n男性人数为："+QString::number(sum.maln)+"\n女性人数为："+QString::number(sum.femn);
    showInfoDlg(s);
}





void MainWindow::on_show_triggered()
{
    choosedlg *dlgcho=new choosedlg(this);
    Qt::WindowFlags flags=dlgcho->windowFlags();
    dlgcho->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    int ret = dlgcho->exec();
    if (ret == QDialog::Accepted)
    {
        cho res = dlgcho->ifchosed();
        ui->txt->document()->clear();
        ui->txt->insertPlainText(a.output1(res.allc||res.teac,res.malc+res.femc));
        ui->txt->insertPlainText(a.output2(res.allc||res.assc,res.malc+res.femc));
        ui->txt->insertPlainText(a.output3(res.allc||res.stac,res.malc+res.femc));
        ui->txt->insertPlainText(a.output4(res.allc||res.tstc,res.malc+res.femc));
    }
}




void MainWindow::showWarningDlg(QString strInfo)
{
    QString dlgTitle="错误";
    QMessageBox *box = new QMessageBox(QMessageBox::Warning, dlgTitle, strInfo, QMessageBox::Ok);
    box->setModal(false);
    box->setWindowIcon(QIcon("../icon/myicon.ico"));
    box->setFixedSize(400,200);
    box->setIconPixmap(QPixmap(""));
    box->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    box->setStyleSheet("color:red");
    box->exec();
}






void MainWindow::showInfoDlg(QString strInfo)
{
    QString dlgTitle="提示";
    QMessageBox *box = new QMessageBox(QMessageBox::Warning, dlgTitle, strInfo, QMessageBox::Ok);
    box->setModal(false);
    box->setWindowIcon(QIcon("../icon/myicon.ico"));
    box->setIconPixmap(QPixmap(""));
    box->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    box->setStyleSheet("color:green");
    box->exec();
}







void MainWindow::showaboutDlg()
{
    QString dlgTitle="IMS for Uni v1.0";
    QString strInfo="\n版本信息：高校人员信息管理系统 v1.0\n欢迎交流！";
    QMessageBox *box = new QMessageBox(QMessageBox::Information, dlgTitle, strInfo, QMessageBox::Ok);
    box->setModal(false);
    box->setWindowIcon(QIcon("../icon/myicon.ico"));
    box->setFixedSize(400,400);
    box->setIconPixmap(QPixmap(""));
    box->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    box->setStyleSheet("color:black");
    box->exec();
}



void MainWindow::on_about_triggered()
{
    showaboutDlg();
}


void MainWindow::on_protect_triggered()
{
     QString text = QInputDialog::getText(this, tr("保护文档"), tr("设置密码:"));
     extern QString password;
     password = text;
     ui->save->setEnabled(0);
}



void MainWindow::on_action_triggered()
{
    if(ui->toolBar->isVisible())
    {
        ui->toolBar->hide();
        ui->action->setText("显示工具栏");
        ui->action->setIcon(QIcon("../icon/max.png"));
    }
    else
    {
        ui->toolBar->show();
        ui->action->setText("隐藏工具栏");
        ui->action->setIcon(QIcon("../icon/min.png"));
    }

}

void MainWindow::on_bug_triggered()
{
    QDesktopServices::openUrl(QUrl("http://www.github.com"));
}






void MainWindow::refresh()
{
    ui->txt->document()->clear();
    ui->txt->insertPlainText(a.output1(1,0));
    ui->txt->insertPlainText(a.output2(1,0));
    ui->txt->insertPlainText(a.output3(1,0));
    ui->txt->insertPlainText(a.output4(1,0));
}






