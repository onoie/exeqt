//
// Created by onoie on 17/06/22.
//

#ifndef LENNA_SLIB_H
#define LENNA_SLIB_H

#include <QObject>
#include <QApplication>
#include <QRect>

using namespace std;

enum Position {Center,TopLeft,TopRight,BottomLeft,BottomRight};

class Slib : public QObject{
Q_OBJECT
public:
    explicit Slib(QObject *parent = 0):QObject(parent){
        //Q_UNUSED(parent);
    }
    ~Slib(){}
    static QString qecho(QString str){
        return "QEcho:"+str;
    }

    static void mv(QWidget* w,Position p){
        switch (p) {
            case TopLeft:break;//TODO;
            case TopRight:break;//TODO;
            case BottomLeft:break;//TODO;
            case BottomRight:break;//TODO;
            default://Center
                QRect rect=QApplication::desktop()->availableGeometry();
                int x = rect.width() / 2;
                int y = rect.height() / 2;
                int wx = w->width() / 2;
                int wy = w->height() / 2;
                w->move(x-wx,y-wy);
                break;
        }
    }
};

#endif //LENNA_SLIB_H
