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

//#pragma execution_character_set("utf-8")
using namespace std;

myCommand::myCommand(QString str, QString id)
{
              m_str = str;
              m_id = id;

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
    ui->txt->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->txt->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->txt->verticalScrollBar()->setValue(ui->txt->verticalScrollBar()->maximumHeight());
    ui->txt->setLineWrapMode(QTextEdit::NoWrap);
    ui->save->setEnabled(0);
    ui->save_ano->setEnabled(0);
    ui->close->setEnabled(0);
    ui->export_2->setEnabled(0);
    ui->menu_E->setEnabled(0);
    ui->menu_C->setEnabled(0);
    ui->txt->setEnabled(0);
    m_UndoStack = new QUndoStack(this);
    QAction *undoAction = m_UndoStack->createUndoAction(this);
    QAction *redoAction = m_UndoStack->createRedoAction(this);
    undoAction->setIcon(QIcon("../icon/undo.ico"));
    redoAction->setIcon(QIcon("../icon/redo.ico"));
    ui->menu_E->insertAction(ui->menu_E->actions().value(ui->menu_E->actions().size()), undoAction);
    ui->menu_E->insertAction(undoAction, redoAction);
    ui->menu_E->insertSeparator(redoAction);
    undoAction->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));
    redoAction->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Y));
    connect(undoAction,SIGNAL(triggered()),this,SLOT(refresh()));
    connect(redoAction,SIGNAL(triggered()),this,SLOT(refresh()));
    Sleep(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_new_2_triggered()
{
    a.init();
    if(ui->save->isEnabled())
        showWarningDlg("你的上一个项目未保存");
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存"),"D:",tr("信息管理系统文件(*.ims)"));
    string s = fileName.toStdString();
    if(fileName != "")
    {
        filename = fileName;
        this->setWindowTitle("高校人员信息管理系统@"+filename);
        a.save(s);
        ui->txt->setEnabled(1);
        ui->save->setEnabled(1);
        ui->save_ano->setEnabled(1);
        ui->close->setEnabled(1);
        ui->export_2->setEnabled(1);
        ui->menu_E->setEnabled(1);
        ui->menu_C->setEnabled(1);
        ui->txt->document()->clear();
        ui->txt->insertPlainText(a.output1(1,0));
        ui->txt->insertPlainText(a.output2(1,0));
        ui->txt->insertPlainText(a.output3(1,0));
        ui->txt->insertPlainText(a.output4(1,0));
    }
}




void MainWindow::on_open_triggered()
{
    a.init();
    if(ui->save->isEnabled())
        showWarningDlg("你的上一个项目未保存");
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开"),"D:",tr("信息管理系统文件(*.ims);;""文本文档(*.txt)"));
    filepath= fileName.toStdString();
    if(filepath!="")
    {

        if(a.open(filepath))
        {
            filename = fileName;
            this->setWindowTitle("高校人员信息管理系统@"+filename);
            ui->txt->setEnabled(1);
            ui->txt->document()->clear();
            ui->txt->insertPlainText(a.output1(1,0));
            ui->txt->insertPlainText(a.output2(1,0));
            ui->txt->insertPlainText(a.output3(1,0));
            ui->txt->insertPlainText(a.output4(1,0));
            ui->save_ano->setEnabled(1);
            ui->close->setEnabled(1);
            ui->export_2->setEnabled(1);
            ui->menu_E->setEnabled(1);
            ui->menu_C->setEnabled(1);
        }
        else
        {
            QString text = QInputDialog::getText(this, tr("保护文档"), tr("password:"));
            extern QString password;
            if(text == password)
            {
                filename = fileName;
                this->setWindowTitle("高校人员信息管理系统@"+filename);
                a.openff(filepath);
                ui->txt->setEnabled(1);
                ui->txt->document()->clear();
                ui->txt->insertPlainText(a.output1(1,0));
                ui->txt->insertPlainText(a.output2(1,0));
                ui->txt->insertPlainText(a.output3(1,0));
                ui->txt->insertPlainText(a.output4(1,0));
                ui->save_ano->setEnabled(1);
                ui->close->setEnabled(1);
                ui->export_2->setEnabled(1);
                ui->menu_E->setEnabled(1);
                ui->menu_C->setEnabled(1);
            }
            else
                showWarningDlg("密码不正确！");
        }

    }
}




void MainWindow::on_save_triggered()
{
    a.save(filepath);
    this->setWindowTitle("高校人员信息管理系统@"+filename);
    ui->save->setEnabled(0);
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
        if(ui->save->isEnabled())
            showWarningDlg("你的项目未保存");
        a.init();
        this->setWindowTitle("高校人员信息管理系统");
        ui->txt->document()->clear();
        ui->txt->setEnabled(0);
        ui->save->setEnabled(0);
        ui->save_ano->setEnabled(0);
        ui->close->setEnabled(0);
        ui->export_2->setEnabled(0);
        ui->menu_E->setEnabled(0);
        ui->menu_C->setEnabled(0);
}




void MainWindow::on_quit_triggered()
{

    if(ui->save->isEnabled())
        showWarningDlg("你的项目未保存");
    a.init();
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
            ui->txt->document()->clear();
            ui->txt->insertPlainText(a.output1(1,0));
            ui->txt->insertPlainText(a.output2(1,0));
            ui->txt->insertPlainText(a.output3(1,0));
            ui->txt->insertPlainText(a.output4(1,0));
            showInfoDlg("删除成功\n");
            ui->save->setEnabled(1);
            this->setWindowTitle("高校人员信息管理系统@"+filename+"*");
            m_UndoStack->push(new myCommand("del",text));
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
            if(dlgInfo->id() != "")
                s.id = dlgInfo->id();
            else
                s.id = "缺省";
            if(dlgInfo->name() != "")
                s.name=dlgInfo->name();
            else
                s.name = "缺省";
            if(dlgInfo->sex() != "")
                s.sex=dlgInfo->sex();
            else
                s.id = "缺省";
            if(dlgInfo->age() != "")
                s.age=dlgInfo->age();
            else
                s.age = "缺省";
            if(dlgInfo->profession()!= "")
                s.profession=dlgInfo->profession();
            else
                s.profession = "缺省";
            if(dlgInfo->office() != "")
                s.office=dlgInfo->office();
            else
                s.office = "缺省";
            if(dlgInfo->department() != "")
                s.department=dlgInfo->department();
            else
                s.department = "缺省";
            if(dlgInfo->title() != "")
                s.title=dlgInfo->title();
            else
                s.title = "缺省";
            if(dlgInfo->work() != "")
                s.work=dlgInfo->work();
            else
                s.work = "缺省";
            if(dlgInfo->lab() != "")
                s.lab=dlgInfo->lab();
            else
                s.lab = "缺省";
            a.input(dlgInfo->status(), s);
            showInfoDlg("添加成功\n");
            ui->save->setEnabled(1);
            this->setWindowTitle("高校人员信息管理系统@"+filename+"*");
            m_UndoStack->push(new myCommand("add",s.id));
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
            if(dlgInfo->id() != "")
                s.id = dlgInfo->id();
            else
                s.id = "缺省";
            if(dlgInfo->name() != "")
                s.name=dlgInfo->name();
            else
                s.name = "缺省";
            if(dlgInfo->sex() != "")
                s.sex=dlgInfo->sex();
            else
                s.id = "缺省";
            if(dlgInfo->age() != "")
                s.age=dlgInfo->age();
            else
                s.age = "缺省";
            if(dlgInfo->profession()!= "")
                s.profession=dlgInfo->profession();
            else
                s.profession = "缺省";
            if(dlgInfo->office() != "")
                s.office=dlgInfo->office();
            else
                s.office = "缺省";
            if(dlgInfo->department() != "")
                s.department=dlgInfo->department();
            else
                s.department = "缺省";
            if(dlgInfo->title() != "")
                s.title=dlgInfo->title();
            else
                s.title = "缺省";
            if(dlgInfo->work() != "")
                s.work=dlgInfo->work();
            else
                s.work = "缺省";
            if(dlgInfo->lab() != "")
                s.lab=dlgInfo->lab();
            else
                s.lab = "缺省";
            s.intst = dlgInfo->status();
            a.input(ss.id.toStdString(), s);
            ui->txt->document()->clear();
            ui->txt->insertPlainText(a.output1(1,0));
            ui->txt->insertPlainText(a.output2(1,0));
            ui->txt->insertPlainText(a.output3(1,0));
            ui->txt->insertPlainText(a.output4(1,0));
            showInfoDlg("修改成功\n");
            ui->save->setEnabled(1);
            this->setWindowTitle("高校人员信息管理系统@"+filename+"*");
            m_UndoStack->push(new myCommand(s.id, ss.id));
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
    QDesktopServices::openUrl(QUrl("https://github.com/toplus1s/-"));
}






void MainWindow::refresh()
{
    ui->save->setEnabled(1);
    this->setWindowTitle("高校人员信息管理系统@"+filename+"*");
    ui->txt->document()->clear();
    ui->txt->insertPlainText(a.output1(1,0));
    ui->txt->insertPlainText(a.output2(1,0));
    ui->txt->insertPlainText(a.output3(1,0));
    ui->txt->insertPlainText(a.output4(1,0));
}






