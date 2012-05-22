#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <algorithm>
#include <math.h>
#include <QVector>
#include <QDir>
#include <QFileDialog>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_plot_zoomer.h>

namespace Ui {
class graphics;
}

class graphics : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit graphics(QWidget *parent = 0);
    virtual ~graphics();
    void createGraph(QVector< double > _first, QVector< double > _second, QVector< double > _spaceAll);
protected:
    QwtLegend *leg;
    QwtPlotCurve *firstGraph, *secondGraph, *allGraph;
    QwtPlotZoomer *zoom;
    QVector < double > firstSpace, secondSpace, spaceAll;
    bool saveImage(QwtPlot *saveWidget);
    bool maxWidthHeight(); // считаем максимальную длину и ширину
private:
    Ui::graphics *ui;
    bool graphCreated;
public slots:
    bool slotSaveAsImage();
};

#endif // GRAPHICS_H
