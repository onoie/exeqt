#include "view.h"

View::View(QGraphicsScene *scene, QWidget *parent):QGraphicsView(scene,parent){
    setStyleSheet("background: transparent");
    this->viewport()->setAutoFillBackground(false);
    //this->setBackgroundBrush(QBrush(Qt::gray));
    //this->loadImage(":/720x480.gif");
    this->loadImage(720,480,":/risky.png");
}

void View::paintEvent(QPaintEvent *event){
//    Q_UNUSED( event )
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());
    //painter.fillRect(rect(),QColor(0,0,0,255));

    painter.drawPixmap(0,0,pixmap);

    QFont font;
    font.setBold(true);
    font.setPixelSize(60);
    painter.setFont(font);
    painter.setPen(QPen(Qt::white));
    painter.drawText(painter.window(), Qt::AlignCenter, text);
//    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
//    painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
//    painter.drawRect(300,300,200,80);
}
