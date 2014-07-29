#include "mainwindow.h"
#include <QApplication>
#include<QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.seWindowIcon(QIcon("zx.ico"))，
    MainWindow w;
    w.seWindowIcon(QIcon("zx.ico"))，
    w.show();

    return a.exec();
}
