
#include <stdlib.h>

#include <QApplication>
#include <QtWidgets>
#include <QDebug>

#include "mainwindow.h"
#include "tetrixwindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    //forRand()
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

//    TetrixWindow window;
//    window.show();

    MainWindow w;
    w.show();

    return app.exec();
}
