#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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


class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow(){}
private slots:
    void receiveImageTcpSocketMessage();
private:
    QNetworkAccessManager* networkManager;
    QTcpSocket *textTcpSocket;
    QTcpSocket *imageTcpSocket;
    QByteArray imageData;
};

#endif // MAINWINDOW_H
