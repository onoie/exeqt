#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
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
        pixmap = pixmap.scaled(50,50,Qt::KeepAspectRatio,Qt::FastTransformation);
        pixmapItem->setPixmap(pixmap);
        resize(pixmap.width(),pixmap.height());
        this->update();
    }
protected:
    void paintEvent(QPaintEvent *event){
        Q_UNUSED( event )
        QPainter painter(this);
        painter.fillRect(rect(),QColor(255,255,255,255));
        painter.drawPixmap(0,0,pixmap);
    }
};

#endif // SCREEN_H
