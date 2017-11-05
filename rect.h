#ifndef RECT_H
#define RECT_H

#include <QObject>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDateTime>

class Rect : public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    explicit Rect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = Q_NULLPTR):QGraphicsRectItem(x, y, width, height, parent){
    }
signals:
    void nextReq();
    void textReq(QString);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event){
        //qDebug() << "MousePress";
        //emit textReq(QString("TextRequest:%1").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd-hh:mm:ss.zzz")));
        emit nextReq();
        QGraphicsRectItem::mouseMoveEvent(event);
    }
};

#endif // RECT_H
