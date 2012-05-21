#ifndef POSTOPERATIONS_H
#define POSTOPERATIONS_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QtGlobal>
#include "parser.h"
#include "graphics.h"

namespace Ui {
class postOperations;
}

class postOperations : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit postOperations(QWidget *parent = 0);
    virtual ~postOperations();
    bool getParameters(double _firstSpace, double _secondSpace, QString lPath); // получаем параметры
    int countSpaces; // Количество подсчетов
    double statMistake;

protected:
    parser *parseSpaces;
    graphics *graph;
    double space;
    double firstSpace, secondSpace;
    QString path;
    QString pathToFile;

private:
    Ui::postOperations *ui;
    QString strToSave(); // Формируем строку для записи в файл
public slots:
    void slotSaveToFile();
    void slotStatMistake();
    void slotCreateGraph();
};

#endif // POSTOPERATIONS_H
