#define WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>
#include "mainwindow.h"
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>

#define weigetWidth 400
#define weigetHeight 300
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
     QDesktopWidget* desktopWidget = QApplication::desktop();
    int winWidth=desktopWidget->screenGeometry().width();
    int winHeight=desktopWidget->screenGeometry().height();
    QRect winRect((winWidth-weigetWidth)/2,(winHeight-weigetHeight)/2,weigetWidth,weigetHeight);
    w.setGeometry(winRect);
    w.setFixedSize(400,300);
    w.show();

    return a.exec();
}
