#ifndef VIEW_H
#define VIEW_H

#include "slib.h"
#include "rect.h"

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
    explicit View(QWidget *parent = nullptr):QGraphicsView(parent){
        setStyleSheet("background: transparent");
        this->viewport()->setAutoFillBackground(false);
        //this->setBackgroundBrush(QBrush(Qt::gray));

        QSize desp(720,480);//640,400

        this->setMinimumSize(desp);
        this->setMaximumSize(desp);

        //this->loadImage(":/720x480.gif");
        this->loadImage(720,350,":/risky.png");

        scene = new QGraphicsScene(QRect(0, 0,desp.width(),desp.height()));
        this->setScene(scene);

        Rect *catchall = new Rect(1,1,720-3,480-3);//-1=ForPen
        //connect(catchall,&Rect::nextReq,[=]{ qDebug()<< "HIT" << QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"); });
        catchall->setPen(QPen(Qt::red));
        catchall->setBrush(Qt::black);
        scene->addItem(catchall);


        //AddMouseClickRect
        Rect *rect = new Rect(0,350,this->width()-3,this->height()-353);
        connect(rect,&Rect::nextReq,[=]{
            emit request();
        });
        rect->setPen(QPen(Qt::white));
        rect->setBrush(Qt::gray);
        scene->addItem(rect);

//        QGraphicsPixmapItem pm(QPixmap(":/risky.png"));
//        scene->addItem(&pm);
//       QGraphicsDropShadowEffect* effect	= new QGraphicsDropShadowEffect();
//       effect->setColor( QColor(0,0,0) );
//       effect->setOffset( 5, 5 );
//       effect->setBlurRadius( 20 );
//       pm.setGraphicsEffect(effect);


    }
    QGraphicsScene *scene;
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
    void setText(QString text){
        this->text=text;
    }
    void request(){
        qDebug()<<"Request";
        setText(QString("NextRequest@%1").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd-hh:mm:ss.zzz")));
        update();
    }
private:
    QString text="default";
protected:
    void paintEvent(QPaintEvent *event){
        QGraphicsView::paintEvent(event);
        QPainter painter(viewport());
        //painter.fillRect(rect(),QColor(0,0,0,255));

        painter.drawPixmap(0,0,pixmap);

//        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine));
//        painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
//        painter.drawRect(0,350,this->width()-3,this->height()-353);

        QFont font;
        font.setBold(true);
        font.setPixelSize(30);
        painter.setFont(font);
        painter.setPen(QPen(Qt::white));
        painter.drawText(painter.window(), Qt::AlignCenter, text);


        //    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
        //    painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));
        //    painter.drawRect(300,300,200,80);
    }
};

#endif // VIEW_H
