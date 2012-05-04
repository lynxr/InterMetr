#ifndef POSTOPERATIONS_H
#define POSTOPERATIONS_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QtGlobal>

namespace Ui {
class postOperations;
}

class postOperations : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit postOperations(QWidget *parent = 0);
    virtual ~postOperations();
    bool getParameters(double lSpace, QString lPath); // получаем параметры

protected:
    double space;
    QString path;

private:
    Ui::postOperations *ui;
    QString strToSave(); // Формируем строку для записи в файл
public slots:
    void slotSaveToFile();
};

#endif // POSTOPERATIONS_H
