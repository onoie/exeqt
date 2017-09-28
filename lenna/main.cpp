#include <iostream>
#include <QApplication>
#include <QtWidgets>
#include "mainwindow.h"
#include "slib.h"

const QString cacheDir = "./cache";

int main(int argc, char *argv[]) {
    //std::cout << "Hello, World!" << std::endl;
    //qDebug() << "QtVersion:" << QT_VERSION_STR;

    QApplication app(argc, argv);

    Q_INIT_RESOURCE(resource_file);

    //CreateLocalCacheDirectory
    if(!QDir().exists(cacheDir)) {
        if(!QDir().mkdir(cacheDir)) {
            qDebug("%s %d: Error: QDir().mkdir(appdir)",__FILE__,__LINE__);
            QMessageBox::warning(0,"Error","Cache Directory could not be created.");
            exit(EXIT_FAILURE);
        }
    }

    MainWindow w;
    Slib::mv(&w,Position::Center);
    w.active();

    return app.exec();
}
