#include "parser.h"

parser::parser(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Class PARSER created";
}

parser::~parser() {
    qDebug() << "Class PARSER deleted";
}
