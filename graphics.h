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
    
private:
    Ui::graphics *ui;
};

#endif // GRAPHICS_H
