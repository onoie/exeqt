#ifndef SCREEN_H
#define SCREEN_H

#include "slib.h"

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QList>
#include <QMenuBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

class Screen : public QWidget{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);
    virtual ~Screen();
    QImage image;

    QPixmap pixmap;
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem();
    void loadImage(QString path){
        if(!image.load(path)){
            QMessageBox::warning(0,"Warning","not found image");
            return;
        }
        pixmap.convertFromImage(image);
        pixmap = pixmap.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation);
        pixmapItem->setPixmap(pixmap);
        resize(pixmap.width(),pixmap.height());
        this->update();
    }
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // SCREEN_H
