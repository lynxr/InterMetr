#include "graphics.h"
#include "ui_graphics.h"

graphics::graphics(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::graphics)
{
    ui->setupUi(this);
    qDebug() << "CLASS GRAPHICS CREATED";
}

graphics::~graphics()
{
    delete ui;
    qDebug() << "CLASS GRAPHICS DELETED";
}
