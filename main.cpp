#include <QtGui/QApplication>
#include "mainclass.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainClass::translateProg();
    mainClass w;
    w.setWindowTitle("InterMetr 1.0 Beta");
    w.show();
    
    return a.exec();
}
