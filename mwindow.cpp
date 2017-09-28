#include "mwindow.h"
#include "slib.h"
#include "xwidget.h"
#include "screen.h"
#include <QMenuBar>


QT_BEGIN_NAMESPACE
class QApplication;
class QtWidgets;
class QDebug;
class QListWidget;
class QVBoxLayout;
class QHBoxLayout;
QT_END_NAMESPACE

MWindow::MWindow(QWidget *parent) : QMainWindow(parent){
    setAttribute(Qt::WA_TranslucentBackground,true);
//    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    createMenus();
    this->resize(800,600);

    XWidget *xw =  new XWidget();
    setCentralWidget(xw);

    QVBoxLayout *vl = Slib::createVBoxLayout();
    xw->setLayout(vl);

    QHBoxLayout *hl = Slib::createHBoxLayout();
    vl->addLayout(hl);

    QSize screenSize(640,400);

    Screen *screen = new Screen;
    screen->setMinimumSize(screenSize);
    screen->setMaximumSize(screenSize);
    hl->addWidget(screen);


//    networkManager = new QNetworkAccessManager();
//    textTcpSocket = new QTcpSocket();
//    imageTcpSocket = new QTcpSocket();
//    //connect(textTcpSocket,&QTcpSocket::readyRead,[=](){qDebug() << "Recieve";});
//    connect(imageTcpSocket,&QTcpSocket::readyRead,[=](){
//        qDebug() << "readyRead";
//        QByteArray message = imageTcpSocket->readAll();
//        if (message.toInt()) {
//            imageTcpSocket->write(imageData);
//            imageData.resize(0);
//        }
//    });

//    QJsonObject jsonObjPost;
//    jsonObjPost.insert("method", "post");
//    jsonObjPost.insert("message", "Hello1");
//    QByteArray postData = QJsonDocument(jsonObjPost).toJson(QJsonDocument::Compact);
//    QUrl postUrl("http://192.168.128.117:8080");
//    QNetworkRequest postRequest(postUrl);
//    postRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
//    networkManager->post(postRequest, postData);

//    textTcpSocket->abort();
//    textTcpSocket->connectToHost("192.168.128.117", 8081);
//    QJsonObject jsonObjSocket;
//    jsonObjSocket.insert("method", "socket");
//    jsonObjSocket.insert("message", "Hello2");
//    QByteArray textData = QJsonDocument(jsonObjSocket).toJson(QJsonDocument::Compact);
//    textTcpSocket->write(textData);

//    imageTcpSocket->abort();
//    imageTcpSocket->connectToHost("127.0.0.1", 8082);
//    QImage image;
//    image.load("demo.jpg", "JPG");
//    QBuffer buffer(&imageData);
//    image.save(&buffer, "JPG");
//    imageTcpSocket->write(QByteArray::number(imageData.size()));

}

void MWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));

    //AddTestAction
    testAct = new QAction(tr("&Test"),this);
    connect(testAct, SIGNAL(triggered()), this, SLOT(test()));
    fileMenu->addAction(testAct);

    //LoadImageAction
    fileMenu->addSeparator();
    fileMenu->addAction(createQuitAction());

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    //AboutQtAction
    QAction* aboutAct = new QAction(tr("AboutQt"),this);
    connect(aboutAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    helpMenu->addAction(aboutAct);
}
void MWindow::test(){
    QMessageBox::information(0,"Test","TestFunction");
}
QAction* MWindow::createQuitAction(){
    QAction *quitAct;
    quitAct = new QAction(tr("&Quit"),this);
    QObject::connect(quitAct, &QAction::triggered, [=]() {
        exit(EXIT_SUCCESS);
    });
    return quitAct;
}
