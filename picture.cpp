#include "picture.h"
#include <QFileDialog>

picture::picture(QObject *parent) :
    QObject(parent)
{
    PI = 3.141592;
    spaceCircle = 0;
    quadFlag = 0;
    imgLoaded = false;
    lineXY.clear();
    lineXY.resize(5);

    lineQuad.clear();
    lineQuad.resize(4);

    pointQuad.clear();
    pointQuad.resize(4);

}

picture::~picture() {
    qDebug() << "object class picture deleted";
}

bool picture::loadImage(QLabel *&label, QLabel *&status) {
    imgLoaded = false;
    int width = label->width();
    int height = label->height();
    label->setFixedHeight(labelH);
    label->setFixedWidth(labelW);
    QString n;
    QFileDialog dial;
    QPixmap pic;
    QImage pic2;
    //QString n;
    int shirinaNew;
    int visotaNew;
    n = dial.getOpenFileName(0,"Open Image","","JPEG FILES (*.jpg *.JPG *.Jpg *.jPg *.jpG)");
    if(n.isEmpty())
    {
        label->setFixedHeight(labelH);
        label->setFixedWidth(labelW);
        return false;
    }
    dial.close();
    n = QDir::convertSeparators(n);
    pic.load(n);
    int shirina = pic.width();
    int visota = pic.height();
    double koeff;
    if (shirina >= visota)
    {
        koeff = (double)shirina / (double)width;
        }
    else if(shirina < visota)
    {
        koeff = (double)visota / (double)height;
    }
    qDebug() << koeff;
    shirinaNew = shirina / koeff;
    visotaNew = visota / koeff;
    label->setFixedHeight(visotaNew);
    label->setFixedWidth(shirinaNew);
    label->setPixmap(pic);
    //pic2 =  pic.toImage();
    QSize size = QSize(shirinaNew,visotaNew);
    QImage pic3 = QImage(size,QImage::Format_RGB32);
    pic3 = pic.toImage();
    pic2 = pic3;
    QImage pic4 = pic2.scaled(size,Qt::KeepAspectRatio,Qt::FastTransformation);
    pic2 = pic4;
    label->setPixmap(QPixmap::fromImage(pic2));
    img = pic2;
    path = n;
    //saveColors(status);
    QFuture <bool> socketSaveColors = QtConcurrent::run(this,&picture::saveColors,status); // Создаем поток в котором параллельно выполняется функция сохраняющая RGB и Color
    imgLoaded = true;
    return true;
}


bool picture::saveColors(QLabel *&status) {
    int width = img.width();
    int height = img.height();
    int razmer = width*height;
    rgb.clear();
    color.clear();
    // VECTORS RESIZE
    rgb.resize(height+1);
    color.resize(height+1);
    for(int r=0; r<height+1; r++)
    {
        rgb[r].resize(width+1);
        color[r].resize(width+1);
    }
    // VECTORS
    int kolvo = 0; // переменная для вывода на экран количества просчитанных пикселей
    for(int i = 0;i < height;i++) {// i - X
        for(int j=0; j < width;j++) {// j - Y
            rgb[i][j] = img.pixel(j,i);//считываем попиксельно каждый цвет в виде RGB
            color[i][j] = rgb[i][j]; // Переводим RGB в строку для вывода или анализа
            //qDebug() << color[i][j].value();
            kolvo++;
        }
        status->setText(QString("Saved %1 of %2 pixels\n").arg(kolvo).arg(razmer));
    }
    qDebug() << "image width" << width;
    qDebug() << "image height" << height;
    return true;
}

bool picture::makeLine(int x, int y, int razmer) {
    if (!imgLoaded) {
        return false;
    }
    lineXY[0].setLine(x,y,x,y+razmer);
    lineXY[1].setLine(x,y,x,y-razmer);
    lineXY[2].setLine(x,y,x-razmer,y);
    lineXY[3].setLine(x,y,x+razmer,y);
    return true;
}


bool picture::quadCreate(int x, int y) {
    qDebug() << "PRESS " << quadFlag;
    if(quadFlag >= 4) {
        quadFlag = 0;
        return true;
    }
    pointQuad[quadFlag].setX(x);
    pointQuad[quadFlag].setY(y);
    lineQuad[0].setLine(pointQuad[0].x(),pointQuad[0].y(),pointQuad[1].x(),pointQuad[1].y());
    lineQuad[1].setLine(pointQuad[1].x(),pointQuad[1].y(),pointQuad[2].x(),pointQuad[2].y());
    lineQuad[2].setLine(pointQuad[2].x(),pointQuad[2].y(),pointQuad[3].x(),pointQuad[3].y());
    lineQuad[3].setLine(pointQuad[3].x(),pointQuad[3].y(),pointQuad[0].x(),pointQuad[0].y());
    quadFlag++;
    return false;
}

void picture::getVectorSize(double &bok, double &top) {
    bok = (pow(pointQuad[0].x() - pointQuad[1].x(), 2)) + (pow(pointQuad[0].y() - pointQuad[1].y(), 2)); //одна из боковых сторон
    top = (pow(pointQuad[1].x() - pointQuad[2].x(), 2)) + (pow(pointQuad[1].y() - pointQuad[2].y(), 2)); // либо верхняя, либо нижняя
    bok = sqrt(bok);
    top = sqrt(top);
    qDebug() << "BOK=" << bok;
    qDebug() << "TOP=" << top;
}

double picture::getSpaceCircle() {
    double tmpSpaceRect = 0, tmpHalfPerRect = 0, tmpBok = 0, tmpTop = 0, tmpRadius = 0, space = 0;
    getVectorSize(tmpBok,tmpTop);
    tmpSpaceRect = tmpBok*tmpTop;
    tmpHalfPerRect = (tmpBok + tmpTop);
    tmpRadius = tmpSpaceRect / tmpHalfPerRect;
    space = PI*pow(tmpRadius,2);
    return space;
}

void picture::pushToSaveSpace() {
    spaceCircle = getSpaceCircle();
}
