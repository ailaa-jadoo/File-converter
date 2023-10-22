//#include "mainwindow.h"
#include "documentconverter.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DocumentConverter converter;
    converter.resize(300, 100);
    converter.show();
    return a.exec();
}
