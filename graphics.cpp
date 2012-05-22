#include "graphics.h"
#include "ui_graphics.h"

graphics::graphics(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::graphics)
{
    ui->setupUi(this);
    setWindowTitle("InterMetr 1.0 RC1");
    qDebug() << "CLASS GRAPHICS CREATED";
    firstSpace.clear();
    secondSpace.clear();
    spaceAll.clear();
    ui->qwtPlot->setTitle(tr("dependence"));
    ui->qwtPlotAll->setTitle(tr("dependence"));
    leg = new QwtLegend;
    leg->setItemMode(QwtLegend::ReadOnlyItem);
    ui->qwtPlot->insertLegend(leg,QwtPlot::TopLegend);
    ui->qwtPlotAll->insertLegend(leg,QwtPlot::TopLegend);
    QObject::connect(ui->pushSaveImage,SIGNAL(clicked()),this,SLOT(slotSaveAsImage()));
}

graphics::~graphics()
{
    delete ui;
    delete leg;
    delete firstGraph;
    delete secondGraph;
    delete allGraph;
    delete zoom;
    qDebug() << "CLASS GRAPHICS DELETED";
}

void graphics::createGraph(QVector<double> _first, QVector<double> _second, QVector<double> _spaceAll) {
    firstSpace = _first;
    secondSpace = _second;
    spaceAll = _spaceAll;
    maxWidthHeight();
    QVector<double> dataSize;
    for( int i = 0; i <= firstSpace.size(); i++) {
        dataSize.push_back(i);
    }

    zoom = new QwtPlotZoomer(ui->qwtPlot->canvas());
    zoom->setRubberBandPen(QPen(Qt::white));

    firstGraph = new QwtPlotCurve(tr("First Graph"));
    firstGraph->setPen(QPen(Qt::red));
    firstGraph->setRenderHint(QwtPlotItem::RenderAntialiased);

    secondGraph = new QwtPlotCurve(tr("Second Graph"));
    secondGraph->setPen(QPen(Qt::blue));
    secondGraph->setRenderHint(QwtPlotItem::RenderAntialiased);

    allGraph = new QwtPlotCurve(tr("All Graph"));
    allGraph->setPen(QPen(Qt::black));
    allGraph->setRenderHint(QwtPlotItem::RenderAntialiased);

    for(int i = 0; i <= firstSpace.size() - 1; i++) {
        firstGraph->setData(dataSize,firstSpace);
        secondGraph->setData(dataSize,secondSpace);
        allGraph->setData(dataSize,spaceAll);
    }
    firstGraph->attach(ui->qwtPlot);
    secondGraph->attach(ui->qwtPlot);
    allGraph->attach(ui->qwtPlotAll);
    ui->qwtPlot->replot();
}

bool graphics::maxWidthHeight() {
    QVector< double > allMas;
    allMas.clear();
    allMas = firstSpace + secondSpace;
    double max = *std::max_element(allMas.begin(),allMas.end());
    double min = *std::min_element(allMas.begin(),allMas.end());

    double maxAll = *std::max_element(spaceAll.begin(),spaceAll.end());
    double minAll = *std::min_element(spaceAll.begin(),spaceAll.end());

    ui->qwtPlot->setAxisTitle(QwtPlot::yLeft,tr("size Space"));
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,min,max);
    ui->qwtPlot->setAxisTitle(QwtPlot::xBottom,tr("number"));
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,firstSpace.size());

    ui->qwtPlotAll->setAxisTitle(QwtPlot::yLeft,tr("Size Space"));
    ui->qwtPlotAll->setAxisScale(QwtPlot::yLeft,minAll,maxAll);
    ui->qwtPlotAll->setAxisTitle(QwtPlot::xBottom,tr("number"));
    ui->qwtPlotAll->setAxisScale(QwtPlot::xBottom,0,spaceAll.size());
    qDebug() << allMas;
}


bool graphics::slotSaveAsImage() {

}
