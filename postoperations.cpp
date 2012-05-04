#include "postoperations.h"
#include "ui_postoperations.h"

postOperations::postOperations(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::postOperations)
{
    ui->setupUi(this);
    qDebug() << "Post Operations created";
    QObject::connect(ui->pushSaveToFile,SIGNAL(clicked()),this,SLOT(slotSaveToFile()));
}

postOperations::~postOperations()
{
    delete ui;
    qDebug() << "postOperations deleted";
}

bool postOperations::getParameters(double lSpace, QString lPath) {
    space = lSpace;
    path = lPath;
    ui->labelSpace->setText(QString("%1").arg(space));
    return true;
}

void postOperations::slotSaveToFile() {
    QFileDialog dialog;
    QString pathToFile = dialog.getSaveFileName(0,"Select File","","Text files (*.txt)");
        #ifdef Q_OS_LINUX
    QFile file(pathToFile+".txt");
        #else
    QFile file(pathToFile);
        #endif
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << strToSave();
    file.close();
}

QString postOperations::strToSave() {
    QString str = "###### "+path+" ######\n"+"SPACE = "+QString("%1").arg(space)+"\n";
    return str;
}
