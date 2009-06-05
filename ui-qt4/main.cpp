#include <QSettings>
#include <QtGui>
#include <QApplication>

#include "MainWindow.h"
#include "settingsgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w ;
    MainWindow* w = new MainWindow();
    QSettings settings;

    w->show();

    return a.exec();
}
