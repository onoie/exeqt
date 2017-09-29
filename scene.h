#ifndef SCENE_H
#define SCENE_H

//#include <QObject>
#include <QWidget>
#include <QGraphicsScene>

class Scene : public QGraphicsScene{
//    Q_OBJECT
public:
    explicit Scene(const QRectF &sceneRect, QObject *parent = Q_NULLPTR);
};

#endif // SCENE_H
