
//
// Created by onoie on 17/06/21.
//

#include "mainwindow.h"
#include "slib.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createMenus();
    loadImage(":/img/lena.bmp");//DefaultImageLoad
    //TODO QMovie for .gif
//    QTabWidget *xtabs;
//    xtabs = new QTabWidget;
//    xtabs->addTab(new QLabel("Hello Qt!"),"Case1");
//    xtabs->addTab(new QLabel("Hello Qt!"),"Case2");
//    xtabs->addTab(new QLabel("Hello Qt!"),"Case3");
//    setCentralWidget(xtabs);
}
MainWindow::~MainWindow() {}
void MainWindow::active(){
    this->show();
}
//Private
void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));

    //AddTestAction
    testAct = new QAction(tr("&Test"),this);
    connect(testAct, SIGNAL(triggered()), this, SLOT(test()));
    fileMenu->addAction(testAct);

    //LoadImageAction
    QAction *loadImageAct;
    loadImageAct = new QAction(tr("&LoadImage"),this);
    QObject::connect(loadImageAct, &QAction::triggered, [=]() {
        loadImage(
            QFileDialog::getOpenFileName(
                this,tr("Open File"),"/",tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)")
            )
        );
    });
    fileMenu->addAction(loadImageAct);

    fileMenu->addSeparator();
    fileMenu->addAction(createQuitAction());

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    //AboutQtAction
    QAction* aboutAct = new QAction(tr("AboutQt"),this);
    connect(aboutAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    helpMenu->addAction(aboutAct);
}
void MainWindow::test(){
    QMessageBox::information(0,"Test","TestFunction");
}
void MainWindow::loadImage(QString path){
    if(!image.load(path)){
        QMessageBox::warning(0,"Warning","not found image");
        return;
    }
    pixmap.convertFromImage(image);
//    baseWidth  = ;
//    baseHeight = ;
    //pixmap = pixmap.scaled(600,600,Qt::KeepAspectRatio,Qt::FastTransformation);
    pixmapItem->setPixmap(pixmap);
    resize(pixmap.width(),pixmap.height());
    Slib::mv(this,Position::Center);
    this->update();
}
QAction* MainWindow::createQuitAction(){
    QAction *quitAct;
    quitAct = new QAction(tr("&Quit"),this);
    QObject::connect(quitAct, &QAction::triggered, [=]() {
        exit(EXIT_SUCCESS);
    });
    return quitAct;
}
//Protected
void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    //QPixmap image("./img/lena.bmp");
    //QPixmap image(":/img/lena.bmp");
    painter.drawPixmap(0,0,pixmap);
}
