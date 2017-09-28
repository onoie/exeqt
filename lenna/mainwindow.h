//
// Created by onoie on 17/06/21.
//

#ifndef LENNA_MAINWINDOW_H_H
#define LENNA_MAINWINDOW_H_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTabWidget>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QMenu>
#include <QAction>
class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void active();
    QImage image;
    QPixmap pixmap;
    int maxWidth  = 0;
    int maxHeight = 0;
public slots:
    void test();
private:
    QMenu *fileMenu;
    QAction* testAct;
    void createMenus();
    QAction* createQuitAction();
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem();
    void loadImage(QString);
protected:
    void paintEvent(QPaintEvent* event);
};


#endif //LENNA_MAINWINDOW_H_H
