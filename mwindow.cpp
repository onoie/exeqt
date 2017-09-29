#include "mwindow.h"
#include "slib.h"
#include "xwidget.h"
#include "scene.h"
#include "view.h"
#include "rect.h"

MWindow::MWindow(QWidget *parent) : QMainWindow(parent){
    setAttribute(Qt::WA_TranslucentBackground,true);
//    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    createMenus();
    this->resize(800,600);
    int sWidth=720;//640;
    int sHeight=480;//400
    QSize screenSize(sWidth,sHeight);

    XWidget *xw =  new XWidget();
    setCentralWidget(xw);

    QHBoxLayout *hl = Slib::createHBoxLayout();
    xw->setLayout(hl);

    QVBoxLayout *vl = Slib::createVBoxLayout();
    hl->addLayout(vl);

    QList<QString> list;
    list.append("zero");
    qDebug()<<list[0];

//    Scene *scene = new Scene(QRect(0, 0, sWidth, sHeight));
//    View *view = new View(scene);
//    view->setStyleSheet("background: transparent");
////    this->setAutoFillBackground(false);
////    this->viewport()->setAutoFillBackground(false);
//    Rect *rect = new Rect(0,0,200,200);
//    rect->setBrush(Qt::black);
//    scene->addItem(rect);
//    view->setMinimumSize(screenSize);
//    view->setMaximumSize(screenSize);
//    view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
//    view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
//    view->loadImage(":/lena.bmp");
//    vl->addWidget(view);


//QGraphicsScene *m_scene = new QGraphicsScene(QRect(0, 0, 640, 480));     //  シーン矩形部分
Scene *m_scene = new Scene(QRect(0, 0,sWidth,sHeight));
//m_scene->addRect(0, 0, 640, 480, QPen(Qt::black), QBrush(Qt::white));   //  [2]
//QGraphicsView *m_view = new QGraphicsView(m_scene);
View *m_view = new View(m_scene);
//view->setStyleSheet("background: transparent");
//m_view->setAutoFillBackground(false);
m_view->viewport()->setAutoFillBackground(false);
m_view->loadImage(":/720x480.gif");
//m_view->setBackgroundBrush(QBrush(Qt::gray));   //  [1]
m_view->setMinimumSize(screenSize);
m_view->setMaximumSize(screenSize);
m_view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
m_view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
Rect *item = new Rect(0,0,sWidth-1,sHeight-1);//-1=ForPen
item->setPen(QPen(Qt::white));
item->setBrush(Qt::black);
m_scene->addItem(item);
//m_view->show();
vl->addWidget(m_view);


    console = new Console;
    console->setMinimumWidth(sWidth);
    console->setMaximumWidth(sWidth);
    vl->addWidget(console);

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
