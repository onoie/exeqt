#include "view.h"

View::View(QGraphicsScene *scene, QWidget *parent):QGraphicsView(scene,parent){
}

void View::paintEvent(QPaintEvent *event){
//    Q_UNUSED( event )
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());
    //painter.fillRect(rect(),QColor(0,0,0,255));

    painter.drawPixmap(0,0,pixmap);

//    QString text = "Exeqt";
//    QFont font = painter.font();
//    font.setBold(true);
//    painter.setFont(font);
//    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));//ペンをセット
//    painter.setBrush(QBrush(Qt::gray, Qt::SolidPattern));//ブラシセット
//    painter.drawText(painter.window(), Qt::AlignCenter, text);//タイトル描画
//    painter.drawRect(300,300,200,80);
}
