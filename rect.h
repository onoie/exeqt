#ifndef RECT_H
#define RECT_H

#include <QObject>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Rect : public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    explicit Rect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = Q_NULLPTR);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // RECT_H
