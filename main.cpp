#include "mainwindow.h"
#include "projectdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    ProjectDialog d;
    d.show();
    return a.exec();
}
