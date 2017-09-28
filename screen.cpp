#include "screen.h"
Screen::Screen(QWidget *parent) : QWidget(parent){
    loadImage(":/lena.bmp");

    QList<QString> list;
    list.append("zero");
    qDebug()<<list[0];
}
Screen::~Screen(){}

void Screen::paintEvent(QPaintEvent *event){
    Q_UNUSED( event )
    QPainter painter(this);
    painter.fillRect(rect(),QColor(255,255,255,255));

    painter.drawPixmap(0,0,pixmap);

    QString text = "Exeqt";
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));//ペンをセット
    painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));//ブラシセット
    painter.drawText(painter.window(), Qt::AlignCenter, text);//タイトル描画
    painter.drawRect(300,300,200,80);
}
