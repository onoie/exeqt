#ifndef XWIDGET_H
#define XWIDGET_H


#include <QWidget>
#include <QApplication>
#include <QPainter>
#include <QDesktopWidget>
#include <QTimer>

class XWidget : public QWidget{
    Q_OBJECT
public:
    virtual ~XWidget(){}
    XWidget (QWidget *parent = 0,const QString windowTitle="XWidget"): QWidget(parent){
        setWindowTitle(windowTitle);
        setAttribute(Qt::WA_TranslucentBackground,true);
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        this->setStyleSheet(" QGraphicsScene { border: none; } ");
    }
    void showAndAllwaysTop(bool checked){
        Qt::WindowFlags flags = this->windowFlags();
        if (checked){
            this->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
            this->show();
        }else{
            this->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
            this->show();
        }
    }
    void moveToAvailableCenter(){
        this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
    }
    void moveToAvailableLeftTop(){
        this->move(QApplication::desktop()->availableGeometry().left(),QApplication::desktop()->availableGeometry().top());
    }
    void moveToAvailableRightBottom(){
        this->move(QApplication::desktop()->availableGeometry().width()-this->width(),QApplication::desktop()->availableGeometry().height()-this->height());
    }
    void resizeToAvailableFullscreen(){
        this->resize(QApplication::desktop()->availableGeometry().width(),QApplication::desktop()->availableGeometry().height());
    }

protected:
    void paintEvent(QPaintEvent *event){
        Q_UNUSED( event )
        QPainter(this).fillRect(rect(),QColor(34,34,34,128));
    }
};


#endif // XWIDGET_H
