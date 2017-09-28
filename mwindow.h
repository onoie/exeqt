#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
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
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QMenu>
#include <QAction>
#include <QGraphicsPixmapItem>
#include <QMenuBar>
#include <QFileDialog>


class MWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MWindow(QWidget *parent = nullptr);
//    QNetworkAccessManager* networkManager;
//    QTcpSocket *textTcpSocket;
//    QTcpSocket *imageTcpSocket;
//    QByteArray imageData;
public slots:
    void test();
private:
    QMenu *fileMenu;
    QAction* testAct;
    void createMenus();
    QAction* createQuitAction();
};

#endif // MWINDOW_H
