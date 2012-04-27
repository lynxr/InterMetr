#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QMenu>
#include "picture.h"

namespace Ui {
class mainClass;
}

class mainClass : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit mainClass(QWidget *parent = 0);
    virtual ~mainClass();
protected:
    picture *image;
    int lineHeight; // для линии сюда записывается высота загруженной картинки
private:
    int razmer; // размер линии для вспомоготельных координат
    QVector < QAction*> act; // массив указателей для меню
    QVector < double > tmpSpaceCircle; // сюда записываем площадь окружносей для хранения
    int iSpaceCircle; // для счетчика tmpSpaceCircle
    QMenu *menu;
    bool menuCreate();
    Ui::mainClass *ui;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void paintEvent(QPaintEvent *event);
public slots:
    void slotLoadImg();
    bool slotMenuPlus();
    bool slotMenuMinus();
    void slotGetSpace();
};

#endif // MAINCLASS_H
