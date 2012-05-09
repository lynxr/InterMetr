#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QDebug>

class parser : public QObject
{
    Q_OBJECT
public:
    explicit parser(QObject *parent = 0);
    virtual ~parser();
    
signals:
    
public slots:
    
};

#endif // PARSER_H
