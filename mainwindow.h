#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<string>
#include<QDialog>
#include<qundostack.h>
#include "qwdialogsize.h"
#include "global.h"

using namespace std;

extern class system a;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_open_triggered();
    void on_save_triggered();
    void on_save_ano_triggered();
    void on_new_2_triggered();
    void on_export_2_triggered();
    void on_close_triggered();
    void on_quit_triggered();
    void on_del_triggered();
    void showWarningDlg(QString strInfo);
    void showaboutDlg();
    void showInfoDlg(QString strInfo);
    void on_find_triggered();
    void on_add_triggered();
    void on_edit_triggered();
    void on_addup_triggered();
    void on_about_triggered();
    void on_show_triggered();
    void refresh();
    void on_protect_triggered();
    void on_action_triggered();
    void on_bug_triggered();

private:
    Ui::MainWindow *ui;
    string filepath;
    QUndoStack *m_UndoStack;
    QString filename = "";

};


class myCommand: public QUndoCommand
{
public:
    myCommand(QString str,QString id);
    void redo();
    void undo();
private:
    QString m_str, m_id;
};



#endif // MAINWINDOW_H
