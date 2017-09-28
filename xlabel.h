#ifndef XLABEL_H
#define XLABEL_H


#include <QLabel>
#include <QMouseEvent>
class XLabel : public QLabel{
Q_OBJECT
public:
    explicit XLabel( const QString& text="", QWidget* parent=0 ): QLabel(parent){
        setText(text);
    }
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event){
        this->setStyleSheet("QLabel { background-color:gray; }");
        emit clicked();
        event->accept();
    }
    void mouseReleaseEvent(QMouseEvent* event){
        this->setStyleSheet("QLabel { background-color:transparent; }");
        event->accept();
    }
};

#endif // XLABEL_H
