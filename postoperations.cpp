#include "postoperations.h"
#include "ui_postoperations.h"

postOperations::postOperations(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::postOperations), countSpaces(0)
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
    if(ui->checkRememberFileName->isChecked() && !pathToFile.isEmpty()) {
        QFile file(pathToFile);
        file.open(QIODevice::Append | QIODevice::Text);
        QTextStream out(&file);
        out << strToSave();
        file.close();
        ui->labelTotalSpaces->setText(QString("Count spaces = %1").arg(++countSpaces));
        return;
    }
    QFileDialog dialog;
        #ifdef Q_OS_LINUX
    pathToFile = dialog.getSaveFileName(0,"Select File","","Text files (*)");
        #else
    pathToFile = dialog.getSaveFileName(0,"Select File","","Text files (*.txt)");
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
    ui->labelTotalSpaces->setText(QString("Count spaces = %1").arg(++countSpaces));
    ui->checkRememberFileName->setEnabled(true);
    ui->checkRememberFileName->setChecked(true);
}

QString postOperations::strToSave() {
    QString str = "###### "+path+" ######\n"+QString("%1").arg(space)+"\n";
    return str;
}
