#include "mainclass.h"
#include "ui_mainclass.h"

mainClass::mainClass(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainClass), razmer(200), post(NULL)
{
    ui->setupUi(this);
    iSpaceCircle = 0;
    tmpSpaceCircle.clear();
    tmpSpaceCircle.resize(2);
    act.resize(2);
    menu = new QMenu(this);
    menuCreate(); // создание меню циклом
    image = new picture;
    image->labelH = ui->labelPic->height();
    image->labelW = ui->labelPic->width();
    QObject::connect(ui->pushLoad,SIGNAL(clicked()),this,SLOT(slotLoadImg()));
    QObject::connect(ui->pushSaveSpace,SIGNAL(clicked()),this,SLOT(slotGetSpace()));
    QObject::connect(ui->pushOperations,SIGNAL(clicked()),this,SLOT(slotNewPostOperation()));
}

mainClass::~mainClass()
{
    post->close();
    for(int i = 0; i <= act.size() - 1; i++) { // удаление указателей для меню, исходя из размера
        delete act[i];
        qDebug() << "action deleted";
    }
    delete menu;
    delete image;
    delete post;
    delete ui;
    qDebug() << "object mainClass deleted";
}

void mainClass::slotLoadImg() {
    if(image->loadImage(ui->labelPic,ui->labelStatus)) {

        if(image->img.width() >= image->img.height()) {
        lineHeight = image->img.width();
        }
        else {
            lineHeight = image->img.height();
        }
        ui->labelMesages->setText(QString::fromUtf8("Все считано, можно выделять"));
    }
}


void mainClass::slotGetSpace() {
    if(!image->imgLoaded || image->quadFlag < 4) {
        return;
    }
    ui->labelMesages->setText(QString::fromUtf8("Выделено %1 квадратов").arg(iSpaceCircle + 1));
    image->pushToSaveSpace();
    tmpSpaceCircle[iSpaceCircle++] = image->spaceCircle;

    // далее для того чтобы убрать все нарисованной с экрана
    for(int i = 0; i <= image->pointQuad.size() - 1; i++) {
        image->pointQuad[i].setX(0);
        image->pointQuad[i].setY(0);
        image->lineQuad[i].setLine(0,0,0,0);
    }
    image->quadFlag = 0;
    update();
    // конец

    if(iSpaceCircle >= 2) {
        if(post == NULL) { // проверяем, выделена ли память под класс настроек, нафига еще раз выделять и херить указатель на предыдущий класс
                post = new postOperations;  // Все квадраты выделены, выделяем память для класса настроек(Каламбурчик =) )
        }
        post->getParameters(tmpSpaceCircle[0] / tmpSpaceCircle[1], image->path);
        ui->lineResult->setText(QString("%1").arg(tmpSpaceCircle[0] / tmpSpaceCircle[1]));
        tmpSpaceCircle[0] = 0; //                       Обнуляем
        tmpSpaceCircle[1] = 0; // переменные для того чтобы сохранить следующую площадь
        //qDebug() << post->space << "POST SPACE";
        iSpaceCircle = 0;
        return;
    }
}

void mainClass::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {

    case Qt::Key_Escape:
        iSpaceCircle = 0;
        ui->labelMesages->setText(QString::fromUtf8("Выделено %1 квадратов").arg(iSpaceCircle));

        for(int i = 0; i <= tmpSpaceCircle.size() - 1; i++) {
            tmpSpaceCircle[i] = 0;
        }

        for(int i = 0; i <= image->pointQuad.size() - 1; i++) {
            image->pointQuad[i].setX(0);
            image->pointQuad[i].setY(0);
            image->lineQuad[i].setLine(0,0,0,0);
        }
        image->quadFlag = 0;
        update();
        break;

    case Qt::Key_Plus:
        if(razmer + 50 >= lineHeight) {
            break;
        }
        razmer += 50;
        update();
        break;

    case Qt::Key_Minus:
        if(razmer - 50 <= 25) {
            break;
        }
        razmer -= 50;
        update();
        break;
    }
}

void mainClass::mouseMoveEvent(QMouseEvent *event) {
    if(event->x() >= image->img.width() || event->y() >= image->img.height() || event->x() <= -image->img.width() || event->y() <= -image->img.height()) { //Чтобы за границу картинки не заходило
        return;
    }
    image->makeLine(event->x(),event->y(),razmer);
    update();
}

void mainClass::mousePressEvent(QMouseEvent *event) {
    if(event->x() >= image->img.width() || event->y() >= image->img.height() || event->x() <= -image->img.width() || event->y() <= -image->img.height()) { //Чтобы за границу картинки не заходило
        return;
    }
    switch(event->button()) {
    case Qt::LeftButton:
        image->quadCreate(event->x(),event->y());
        update();
        break;
    }

}

void mainClass::paintEvent(QPaintEvent *event) {
    if(!image->imgLoaded) {
        return;
    }
    QImage img(image->img);
    QPainter paint(&img);
    paint.setPen(QPen(Qt::red,5,Qt::SolidLine));
    if(image->quadFlag >= 4) {
        for(int i= 0; i <= image->lineQuad.size() - 1; i++) {
            //qDebug() << "LINE DRAWED";
            paint.drawLine(image->lineQuad[i]);
        }
    }
    for(int i = 0; i <= image->pointQuad.size() - 1; i++) {
        paint.drawPoint(image->pointQuad[i].x(),image->pointQuad[i].y());
    }
    paint.setPen(QPen(Qt::black,2,Qt::SolidLine));
    for(int i = 0; i <= 4; i++) {
        paint.drawLine(image->lineXY[i]);
    }
    ui->labelPic->setPixmap(QPixmap::fromImage(img));

}

void mainClass::contextMenuEvent(QContextMenuEvent *event) {
    menu->exec(event->globalPos());
}

bool mainClass::slotMenuPlus() {
    if(razmer + 50 >= lineHeight) {
        return false;
    }
    razmer += 50;
    return true;
}

bool mainClass::slotMenuMinus() {
    if (razmer - 50 <= 25) {
        return false;
    }
    razmer -= 50;
    return true;
}

bool mainClass::menuCreate() {
   act[0] = new QAction("(+) Plus",this);
   connect(act[0],SIGNAL(triggered()),SLOT(slotMenuPlus()));
   menu->addAction(act[0]);

   act[1] = new QAction("(-) Minus",this);
   connect(act[1],SIGNAL(triggered()),SLOT(slotMenuMinus()));
   menu->addAction(act[1]);
   return true;
}

void mainClass::slotNewPostOperation() {
    if(post == NULL) {  // зачем зря выделять память, если клиент не прибегнет к настройкам
        QMessageBox::warning(this,"WARNING","Too early, please select lines");
        return;
    }
    post->setWindowTitle("InterMetr v 1.0 Beta");
    post->show();
}
