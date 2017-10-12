#ifndef VIEW_H
#define VIEW_H

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
#include <QString>

class View : public QGraphicsView{
public:
    explicit View(QGraphicsScene *scene, QWidget *parent = nullptr);
    QImage image;
    QPixmap pixmap;
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem();
    void loadImage(int scaleX,int scaleY,QString path){
        if(!image.load(path)){
            QMessageBox::warning(0,"Warning","not found image");
            return;
        }
        pixmap.convertFromImage(image);
        if(scaleX!=0||scaleY!=0){
            pixmap = pixmap.scaled(scaleX,scaleY,Qt::KeepAspectRatio,Qt::FastTransformation);
        }
        pixmapItem->setPixmap(pixmap);
        resize(pixmap.width(),pixmap.height());
        this->update();
    }
public slots:
    void updateText(QString text){
        this->text=text;
    }
private:
    QString text="default";
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // VIEW_H
