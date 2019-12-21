#ifndef CHOOSEDLG_H
#define CHOOSEDLG_H

#include <QDialog>

namespace Ui {
class choosedlg;
}



class cho{
public:
    int teac, assc, stac, tstc, malc, femc, allc;

};

class choosedlg : public QDialog
{
    Q_OBJECT


public:
    explicit choosedlg(QWidget *parent = nullptr);
    ~choosedlg();
    cho ifchosed();

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::choosedlg *ui;
};

#endif // CHOOSEDLG_H
