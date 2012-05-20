#include "graphics.h"
#include "ui_graphics.h"

graphics::graphics(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::graphics)
{
    ui->setupUi(this);
    qDebug() << "CLASS GRAPHICS CREATED";
    firstSpace.clear();
    secondSpace.clear();
}

graphics::~graphics()
{
    delete ui;
    qDebug() << "CLASS GRAPHICS DELETED";
}

bool graphics::saveFirstSpace(double _space) {
    firstSpace.push_back(_space);
    qDebug() << QString("FIRST=%1").arg(_space);
    return true;
}

bool graphics::saveSecondSpace(double _space) {
    secondSpace.push_back(_space);
    qDebug() << QString("SECOND=%1").arg(_space);
    return true;
}
