#include "mainwindow.h"
#include<QApplication>
#include<QPixmap>
#include<QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication m(argc, argv);
    QPixmap pixmap("../icon/welcome.png");
    QSplashScreen splash(pixmap);
    splash.show();    //启动图
    m.processEvents();
    MainWindow w;
    w.show();
    splash.finish(&w);
    return m.exec();
}
