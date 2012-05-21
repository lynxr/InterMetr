#include "parser.h"

parser::parser(QString lPath, QObject *parent) :
    QObject(parent), path(lPath)
{
    qDebug() << "Class PARSER created"+ path;
    spaces.clear();
    firstSpaces.clear();
    secondSpaces.clear();
}

parser::~parser() {
    qDebug() << "Class PARSER deleted";
}

QVector< double > parser::parse() {
    spaces.clear();
    firstSpaces.clear();
    secondSpaces.clear();
    QRegExp exprSALL("SALL (.?[0-9]+\.[0-9]+).?"); // для площади
    QRegExp exprS1("S1 (.?[0-9]+\.[0-9]+).?"); // для первого квадрата
    QRegExp exprS2("S2 (.?[0-9]+\.[0-9]+).?"); // для второго квадрата
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    for(int i=0; !file.atEnd(); i++) {
        QString tmpSpace = file.readLine();
        bool SALL = exprSALL.exactMatch(tmpSpace);
        bool S1 = exprS1.exactMatch(tmpSpace);
        bool S2 = exprS2.exactMatch(tmpSpace);
        if(SALL)
        {
            spaces.push_back(exprSALL.cap(1).toDouble());
        }
        if(S1)
        {
            firstSpaces.push_back(exprS1.cap(1).toDouble());
        }
        if(S2)
        {
            secondSpaces.push_back(exprS2.cap(1).toDouble());
        }
    }
    file.close();
    return spaces;
}

double parser::sredKvOtkl(double sredArifm, QVector< double > vector) {
    double sum = 0, Sx = 0;
    for(int i = 0; i < vector.size() - 1; i++) {
        sum += pow( vector[i] - sredArifm, 2);
    }
    Sx = sqrt( sum / (vector.size() - 2) );
    return Sx;
}

void parser::switchFile(QString _file) {
    path = _file;
}

double parser::statMistake() {
    parse();
    double sredArifmetic = 0; //Среднее арифметическое
    for(int i = 0; i < spaces.size() - 1; i++) {
        sredArifmetic += spaces[i];
    }
    sredArifmetic /= spaces.size();
    double Sx = sredKvOtkl(sredArifmetic,spaces);
    double mistake = Sx / sqrt(spaces.size() - 1);
    qDebug() << tr("MISTAKE=%1").arg(mistake);
    return mistake;
}

bool parser::createGraph(QVector< double > &_first, QVector< double > &_second, QVector<double> &_spaceAll) {
    parse();
    _first = firstSpaces;
    _second = secondSpaces;
    _spaceAll = spaces;
    return true;
}
