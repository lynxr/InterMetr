#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <math.h>

class parser : public QObject
{
    Q_OBJECT
public:
    explicit parser(QString lPath,QObject *parent = 0);
    virtual ~parser();
    QVector<double> parse();
    double statMistake(); // функция определения статистической ошибки

protected:
    QString path;
    QVector< double > spaces;
    double sredKvOtkl(double sredArifm, QVector<double> vector); // среднеквадратичное отклонение
signals:
    
public slots:
    
};

#endif // PARSER_H
