#include "rect.h"

Rect::Rect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent):QGraphicsRectItem(x, y, width, height, parent){
}
void Rect::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "MousePress";
}
