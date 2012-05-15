#ifndef POSTOPERATIONS_H
#define POSTOPERATIONS_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QtGlobal>
#include "parser.h"

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
    int countSpaces; // Количество подсчетов
    double statMistake;

protected:
    parser *parseSpaces;
    double space;
    QString path;
    QString pathToFile;

private:
    Ui::postOperations *ui;
    QString strToSave(); // Формируем строку для записи в файл
public slots:
    void slotSaveToFile();
    void slotParseFromFile();
};

#endif // POSTOPERATIONS_H
