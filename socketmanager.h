#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QVBoxLayout>
#include <QBuffer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTcpSocket>
#include <QDataStream>

class SocketManager{
public:
    QDataStream::Version qtversion = QDataStream::Qt_5_9;
    QString host;
    int port;
    SocketManager(QString host,int port){
        this->host=host;
        this->port=port;
        networkManager = new QNetworkAccessManager();
        tcpSocket = new QTcpSocket();
        //    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
        //    connect(&tcpSocket, SIGNAL(disconnected()),this, SLOT(closeConnection()));
        //    connect(&tcpSocket, SIGNAL(readyRead()),this, SLOT(updateMessage()));
        //    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(error()));
    }
    void init(){
        tcpSocket->abort();
        tcpSocket->connectToHost(host, port);
    }
    void sendJsonObjectExample(){
        QJsonObject jsonObjSocket;
        jsonObjSocket.insert("result","ok");
        jsonObjSocket.insert("date", QDateTime::currentDateTime().toString());
        sendJsonObject(jsonObjSocket);
    }
    void sendJsonObject(QJsonObject jsonObjSocket){
        QByteArray textData = QJsonDocument(jsonObjSocket).toJson(QJsonDocument::Compact);
        tcpSocket->write(textData);
    }
    void sendByteArrayExample(){
        QString string = "ByteArrayString";
        sendByteArray(string);
    }
    void sendByteArray(QString string){
        init();
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(qtversion);
        out << quint16(0);
        //out << quint16(string.size()) <<  string;
        out << quint16(string.size()) <<  string.toUtf8();
        tcpSocket->write(block);
    }
private:
    QNetworkAccessManager* networkManager;
    QTcpSocket *tcpSocket;
    quint16 nextBlockSize;
};

#endif // SOCKETMANAGER_H
