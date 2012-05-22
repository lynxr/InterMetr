#include "postoperations.h"
#include "ui_postoperations.h"

postOperations::postOperations(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::postOperations), countSpaces(0), parseSpaces(NULL), space(NULL), graph(NULL)
{
    ui->setupUi(this);
    qDebug() << "Post Operations created";
    QObject::connect(ui->pushSaveToFile,SIGNAL(clicked()),this,SLOT(slotSaveToFile()));
    QObject::connect(ui->pushStatistic,SIGNAL(clicked()),this,SLOT(slotStatMistake()));
    QObject::connect(ui->pushCreateGraph,SIGNAL(clicked()),this,SLOT(slotCreateGraph()));
}

postOperations::~postOperations()
{
    delete ui;
    if(parseSpaces != NULL) {
        delete parseSpaces;
    }
    if(graph != NULL) {
        delete graph;
    }
    qDebug() << "postOperations deleted";
}

bool postOperations::getParameters(double _firstSpace, double _secondSpace, QString lPath) {
    space = _firstSpace / _secondSpace;
    firstSpace = _firstSpace;
    secondSpace = _secondSpace;
    path = lPath;
    ui->labelSpace->setText(QString("%1").arg(space));
    return true;
}

void postOperations::slotSaveToFile() {
    if(space == NULL) {
        ui->labelSpace->setText(QString("%1").arg(0));
        return;
    }
    if(ui->checkRememberFileName->isChecked() && !pathToFile.isEmpty()) {

        QFile file(pathToFile);
        file.open(QIODevice::Append | QIODevice::Text);
        QTextStream out(&file);
        out << strToSave();
        file.close();
        ui->labelTotalSpaces->setText(tr("Count spaces = %1").arg(++countSpaces));
        return;
    }
    QFileDialog dialog;
        #ifdef Q_OS_LINUX
    pathToFile = dialog.getSaveFileName(0,tr("Select File"),"",tr("Text files (*)"));
        #else
    pathToFile = dialog.getSaveFileName(0,tr("Select File"),"",tr("Text files (*.txt)"));
        #endif
    if(pathToFile.isEmpty()) {
        qDebug() << "EMPTY";
        ui->checkRememberFileName->setEnabled(false);
        return;
        }
    QFile file(pathToFile);
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << strToSave();
    file.close();
    ui->labelTotalSpaces->setText(tr("Count spaces = %1").arg(++countSpaces));
    ui->checkRememberFileName->setEnabled(true);
    ui->checkRememberFileName->setChecked(true);
}

QString postOperations::strToSave() {
    QString str = "###### "+path+" ######\n"+QString("SALL %1").arg(space)+"\n"+QString("S1 %1").arg(firstSpace)+"\n"+QString("S2 %2").arg(secondSpace)+"\n";
    return str;
}


void postOperations::slotStatMistake() {
        QFileDialog dial;
        #ifdef Q_OS_LINUX
        QString file = dial.getOpenFileName(0,tr("Select File"),"",tr("Text files (*)"));
        #else
        QString file = dial.getOpenFileName(0,tr("Select File"),"",tr("Text files (*.txt)"));
        #endif
        if(!file.isEmpty()) {
            if(parseSpaces == NULL) {
            parseSpaces = new parser(file);
            }
            else {
                parseSpaces->switchFile(file);
            }
            statMistake = parseSpaces->statMistake();
            ui->labelMistake->setText(QString("%1").arg(statMistake));
        }
}

void postOperations::slotCreateGraph() {
    QFileDialog dial;
    #ifdef Q_OS_LINUX
    QString file = dial.getOpenFileName(0,tr("Select File"),"",tr("Text files (*)"));
    #else
    QString file = dial.getOpenFileName(0,tr("Select File"),"",tr("Text files (*.txt)"));
    #endif
    if(!file.isEmpty()) {
        if(parseSpaces == NULL) {
        parseSpaces = new parser(file);
        }
        else {
            parseSpaces->switchFile(file);
        }
        // СЮДА ФУНКЦИЮ ПО ПОСТРОЕНИЮ ГРАФИКА
        if(graph == NULL) {
            graph = new graphics(this);
            graph->show();
        }
        else {
            delete graph;
            graph = new graphics(this);
            graph->show();
        }
        QVector<double> tmpFirstSpace, tmpSecondSpace, tmpAllSpace;
        if(parseSpaces->createGraph(tmpFirstSpace,tmpSecondSpace,tmpAllSpace))
        {
            graph->createGraph(tmpFirstSpace,tmpSecondSpace,tmpAllSpace);
        }
    }
}
