#include "parser.h"

parser::parser(QString lPath, QObject *parent) :
    QObject(parent), path(lPath)
{
    qDebug() << "Class PARSER created"+ path;
    spaces.clear();
}

parser::~parser() {
    qDebug() << "Class PARSER deleted";
}

QVector< double > parser::parse() {
    spaces.clear();
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    for(int i=0; !file.atEnd(); i++) {
        QString tmpSpace = file.readLine();
        if(i % 2 != 0)
        {
            spaces.push_back(tmpSpace.toDouble());
        }
    }
    file.close();
    return spaces;
}

double parser::statMistake() {
    double sredArifmetic = 0; //Среднее арифметическое
    QVector < double > space = parse();
    for(int i = 0; i < space.size() - 1; i++) {
        sredArifmetic += space[i];
    }
    sredArifmetic /= space.size();
    double Sx = sredKvOtkl(sredArifmetic,space);
    double mistake = Sx / sqrt(space.size() - 1);
    qDebug() << tr("MISTAKE=%1").arg(mistake);
    return mistake;
}

double parser::sredKvOtkl(double sredArifm, QVector< double > vector) {
    double sum = 0, Sx = 0;
    for(int i = 0; i < vector.size() - 1; i++) {
        sum += pow( vector[i] - sredArifm, 2);
    }
    Sx = sqrt( sum / (vector.size() - 2) );
    return Sx;
}
