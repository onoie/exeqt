
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    networkManager = new QNetworkAccessManager();
    textTcpSocket = new QTcpSocket();
    imageTcpSocket = new QTcpSocket();
    connect(imageTcpSocket, SIGNAL(readyRead()), this, SLOT(receiveImageTcpSocketMessage()));
    QJsonObject jsonObjPost;
    jsonObjPost.insert("method", "post");
    jsonObjPost.insert("message", "biebu.xin");
    QByteArray postData = QJsonDocument(jsonObjPost).toJson(QJsonDocument::Compact);
    QUrl postUrl("http://127.0.0.1:8080");
    QNetworkRequest postRequest(postUrl);
    postRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    networkManager->post(postRequest, postData);
    textTcpSocket->abort();
    textTcpSocket->connectToHost("127.0.0.1", 8081);
    QJsonObject jsonObjSocket;
    jsonObjSocket.insert("method", "socket");
    jsonObjSocket.insert("message", "biebu.xin");
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

void MainWindow::receiveImageTcpSocketMessage(){
    qDebug() << "Recieve";
}
