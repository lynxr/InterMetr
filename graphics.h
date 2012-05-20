#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class graphics;
}

class graphics : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit graphics(QWidget *parent = 0);
    virtual ~graphics();
    bool saveFirstSpace(double _space);
    bool saveSecondSpace(double _space);
protected:
    QVector< double > firstSpace; // хранит первую площадь
    QVector< double > secondSpace; // хранит вторую площадь
    
private:
    Ui::graphics *ui;
};

#endif // GRAPHICS_H
