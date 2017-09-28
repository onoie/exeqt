#ifndef SLIB_H
#define SLIB_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QLabel>
#include <QFontDatabase>
#include <QApplication>
#include <QDesktopWidget>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QPushButton>
#include <QDir>
#include <QProcess>
#include <QDesktopServices>
#include <QTabWidget>
#include <QBoxLayout>
#include <QMessageBox>

#include "xwidget.h"
#include "xlabel.h"

enum MVPosition{
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    CENTER
};

class Slib : public QObject{
    Q_OBJECT
public:
    explicit Slib(QObject *parent = 0) :QObject(parent){
    }
    //	echo method
    static QString echo(const QString str){
        return "SlibEcho:"+str;
    }
    static void createCacheDirectory(QString cacheDir = "./cache"){
        //CreateLocalCacheDirectory
        if(!QDir().exists(cacheDir)) {
            if(!QDir().mkdir(cacheDir)) {
                qDebug("%s %d: Error: QDir().mkdir(appdir)",__FILE__,__LINE__);
                QMessageBox::warning(0,"Error","Cache Directory could not be created.");
                exit(EXIT_FAILURE);
            }
        }
    }
    static QWidget* createWidget(){
        QWidget *w = new QWidget;
        return w;
    }
    static QTabWidget* createTabWidget(){
        QTabWidget *tw = new QTabWidget;
        return tw;
    }
    static void labelStylize(QLabel* label){
        label->setAlignment(Qt::AlignLeft);
        label->setTextFormat(Qt::RichText);
        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
        QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
        font.setPointSize(10);
        label->setFont(font);
        label->setOpenExternalLinks(true);
        label->setStyleSheet(
            "QLabel{"
                "color: rgba(255,255,255,100%);"
                "background-color: rgba(34,34,34,0.7);"
                "padding:3px 5px;"
            "}"
        );
    }
    static void showAndAllwaysTop(QWidget* widget,bool checked){
        Qt::WindowFlags flags = widget->windowFlags();
        if (checked){
            widget->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
            widget->show();
        }else{
            widget->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
            widget->show();
        }
    }
    static void mv(QWidget* widget,MVPosition position=MVPosition::CENTER){
        QRect aa(QApplication::desktop()->availableGeometry());
        switch (position) {
            case TOP_LEFT:
                widget->move(0,0);
                //widget->move(QApplication::desktop()->availableGeometry().left(),QApplication::desktop()->availableGeometry().top());
                break;
            case TOP_RIGHT:
                widget->move(aa.width()-widget->width(),0);
                break;
            case BOTTOM_LEFT:
                widget->move(0,aa.height()-widget->height());
                break;
            case BOTTOM_RIGHT:
                widget->move(aa.width()-widget->width(),aa.height()-widget->height());
                //widget->move(QApplication::desktop()->availableGeometry().width()-widget->width(),QApplication::desktop()->availableGeometry().height()-widget->height());
                break;
            default:
                widget->move(aa.width()/2-widget->width()/2,aa.height()/2-widget->height()/2);
                //widget->move(QApplication::desktop()->availableGeometry().center() - widget->rect().center());
                break;
        }
    }
    void resizeToAvailableFullscreen(QWidget* widget){
        widget->resize(
            QApplication::desktop()->availableGeometry().width(),
            QApplication::desktop()->availableGeometry().height()
        );
    }
    static QString createTextIconStr(QString color,QString iconStr){
        return "<span style=\"color:"+color+";\">"+iconStr+"</span>";
    }
    static std::string qStrToStdStr(QString qstr){
         return qstr.toLocal8Bit().toStdString();
         //return qstr.toUtf8().toStdString();
    }
    static bool isFixedPitch(const QFont & font) {
        const QFontInfo fi(font);
        //qDebug() << fi.family() << fi.fixedPitch();
        return fi.fixedPitch();
    }
    static QFont getMonospaceFont(){
        QFont font("monospace");
        if (isFixedPitch(font)) return font;
        font.setStyleHint(QFont::Monospace);
        if (isFixedPitch(font)) return font;
        font.setStyleHint(QFont::TypeWriter);
        if (isFixedPitch(font)) return font;
        font.setFamily("courier");
        if (isFixedPitch(font)) return font;
        return font;
    }
    static QString getRootPath(){
        return QDir::root().absolutePath();
    }
    static QString getLocalIP(){
        foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)){
                 return address.toString();
            }
        }
        return "127.0.0.1";
    }
    static QStringList getItemList(QString path){
        QDir dir(path);
        QStringList result;
        if(dir.exists()){
            result = dir.entryList();
        }
        return result;
    }
    static QPushButton* createQAppQuitBtn(){
        QPushButton *qQuitBtn;
        qQuitBtn = new QPushButton("QuitButton");
        QObject::connect(qQuitBtn, &QPushButton::clicked, [=]() {
            QApplication::quit();
         });
        return qQuitBtn;
    }
    static QPushButton* createQProcBtn(QString btnText,QString path){
        QPushButton *qProcBtn;
        qProcBtn = new QPushButton(btnText);
        QObject::connect(qProcBtn, &QPushButton::clicked, [=]() {
             executeProcess(path);
         } );
        return qProcBtn;
    }
    static void executeProcess(QString command){
        QProcess::startDetached("\""+command+"\"");
    }
    static QPushButton* createOpenUrlBtn(QString btnText,QString url){
        QPushButton *qOpenUtlBtn;
        qOpenUtlBtn = new QPushButton(btnText);
        QObject::connect(qOpenUtlBtn, &QPushButton::clicked, [=]() {
             openURL(url);
         } );
        return qOpenUtlBtn;
    }
    static void openURL(QString url){
        QDesktopServices::openUrl(QUrl(url));
    }
    static XLabel* createXLabel(QString name){
        XLabel *xlabel = new XLabel(name);
        xlabel->setStyleSheet("QLabel { text-decoration:underline; }");
        QObject::connect(xlabel, &XLabel::clicked, [=]() {
            qDebug()<<"Onclick";
         });
        return xlabel;
    }
    static QVBoxLayout* createVBoxLayout(){
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setSpacing(0);
        vl->setMargin(0);
        return vl;
    }
    static QHBoxLayout* createHBoxLayout(){
        QHBoxLayout *hl = new QHBoxLayout;
        hl->setSpacing(0);
        hl->setMargin(0);
        return hl;
    }
};

#endif // SLIB_H
