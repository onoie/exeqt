
#include "mainwindow.h"
#include "qxp/slib.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    qDebug()<<"HelloWorld";
    Slib::sendTcpSocketExample("localhost",80);
 }

