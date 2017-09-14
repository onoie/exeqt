#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "socketmanager.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow(){}
    SocketManager *socketManager;
};

#endif // MAINWINDOW_H
