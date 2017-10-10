#include "rect.h"

Rect::Rect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent):QGraphicsRectItem(x, y, width, height, parent){
}
void Rect::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //qDebug() << "MousePress";
    //emit textReq(QString("TextRequest:%1").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd-hh:mm:ss.zzz")));
    emit nextReq();
    QGraphicsRectItem::mouseMoveEvent(event);
}
