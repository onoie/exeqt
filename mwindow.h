#ifndef MWINDOW_H
#define MWINDOW_H

#include "console.h"
#include "slib.h"
#include "xwidget.h"
#include "scene.h"
#include "view.h"
#include "rect.h"

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
#include <QLineEdit>

QT_BEGIN_NAMESPACE
class QApplication;
class QtWidgets;
class QDebug;
class QListWidget;
class QVBoxLayout;
class QHBoxLayout;
QT_END_NAMESPACE

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
    void next();
    void serif(QString);
private:
    View *view;
    Console *console;
    QMenu *fileMenu;
    QAction* testAct;
    void createMenus();
    QAction* createQuitAction();
};

#endif // MWINDOW_H
