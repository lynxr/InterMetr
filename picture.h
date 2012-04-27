#ifndef PICTURE_H
#define PICTURE_H

#include <QObject>
#include <QImage>
#include <QDebug>
#include <QLabel>
#include <QRgb>
#include <QtConcurrentRun>
#include <QLine>
#include <math.h>
//#include "mainclass.h"

class picture : public QObject
{
    Q_OBJECT
public:
    explicit picture(QObject *parent = 0);
    virtual ~picture();
    QImage img;
    int labelW; // started label width
    int labelH; // started label height
    QString path;
    bool loadImage(QLabel *&label, QLabel *&status);
    bool saveColors(QLabel*&status); // Сохраняет RGB и Color.name соответственно в rgb и color(см. ниже массивы)
    bool makeLine(int x, int y, int razmer = 200); // создание линии координат
    QVector<QLine > lineXY;
    // для хранения координат вершин квадрата
    bool quadCreate(int x, int y); //Построение квадрата и соответственно вписанной окружности
    int quadFlag; // счетчик количества сохраненных координат
    QVector<QPoint > pointQuad; // хранит координаты вершин квадрата, в который вписывается окружность
    QVector<QLine > lineQuad;
    bool imgLoaded; // проверка загружена ли картинка

    // ################# ПЛОЩАДЬ ОКРУЖНОСТИ #######################
    void pushToSaveSpace(); // вызывается для сохранения площади в public переменной spaceCircle (см. ниже)
    double spaceCircle; // УРАААА ВОТ И ПЛОЩАДЬ ОКРУЖНОСТИ
protected:
    // ################# считаем площадь вписанной окружности ######################
    void getVectorSize(double &bok, double &top); // записывает в переменные длину вектора боковой и либо верхней, либо нижней грани - впринципе пофиг
    double getSpaceCircle(); // вспомогательная функция, возвращает радиус окружности

    QVector<QVector<QRgb> >  rgb; // Хранит RGB для последущего анализа
    QVector<QVector<QColor> >  color; // Хранит color для последущего анализа (Можно вызвать color.name)
private:
    const double PI = 3.141592;
signals:

public slots:

};

#endif // PICTURE_H
