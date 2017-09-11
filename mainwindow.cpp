
#include "mainwindow.h"

//MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
//    qDebug()<<"HelloWorld";
//    networkManager = new QNetworkAccessManager();
//    textTcpSocket = new QTcpSocket();
//    imageTcpSocket = new QTcpSocket();
//    connect(textTcpSocket,&QTcpSocket::readyRead,[=](){qDebug() << "Recieve";});
//    connect(imageTcpSocket,&QTcpSocket::readyRead,[=](){qDebug() << "ImageRecieve";});

//    QJsonObject jsonObjPost;
//    jsonObjPost.insert("method", "post");
//    jsonObjPost.insert("message", "Hello1");
//    QByteArray postData = QJsonDocument(jsonObjPost).toJson(QJsonDocument::Compact);
//    QUrl postUrl("http://127.0.0.1:8080");
//    QNetworkRequest postRequest(postUrl);
//    postRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
//    networkManager->post(postRequest, postData);

//    textTcpSocket->abort();
//    textTcpSocket->connectToHost("127.0.0.1", 8081);
//    QJsonObject jsonObjSocket;
//    jsonObjSocket.insert("method", "socket");
//    jsonObjSocket.insert("message", "Hello2");
//    QByteArray textData = QJsonDocument(jsonObjSocket).toJson(QJsonDocument::Compact);
//    textTcpSocket->write(textData);
// }


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    networkManager = new QNetworkAccessManager();
    textTcpSocket = new QTcpSocket();
    imageTcpSocket = new QTcpSocket();
    //connect(textTcpSocket,&QTcpSocket::readyRead,[=](){qDebug() << "Recieve";});
    connect(imageTcpSocket,&QTcpSocket::readyRead,[=](){
        qDebug() << "readyRead";
        QByteArray message = imageTcpSocket->readAll();
        if (message.toInt()) {
            imageTcpSocket->write(imageData);
            imageData.resize(0);
        }
    });

    QJsonObject jsonObjPost;
    jsonObjPost.insert("method", "post");
    jsonObjPost.insert("message", "Hello1");
    QByteArray postData = QJsonDocument(jsonObjPost).toJson(QJsonDocument::Compact);
    QUrl postUrl("http://192.168.128.117:8080");
    QNetworkRequest postRequest(postUrl);
    postRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    networkManager->post(postRequest, postData);

    textTcpSocket->abort();
    textTcpSocket->connectToHost("192.168.128.117", 8081);
    QJsonObject jsonObjSocket;
    jsonObjSocket.insert("method", "socket");
    jsonObjSocket.insert("message", "Hello2");
    QByteArray textData = QJsonDocument(jsonObjSocket).toJson(QJsonDocument::Compact);
    textTcpSocket->write(textData);

    imageTcpSocket->abort();
    imageTcpSocket->connectToHost("127.0.0.1", 8082);
    QImage image;
    image.load("demo.jpg", "JPG");
    QBuffer buffer(&imageData);
    image.save(&buffer, "JPG");
    imageTcpSocket->write(QByteArray::number(imageData.size()));
}
