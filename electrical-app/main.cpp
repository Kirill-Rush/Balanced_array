#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *pWindow = new MainWindow;
    pWindow->show();
    return a.exec();
}
