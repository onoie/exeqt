#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QLineEdit>
#include <QDebug>
#include <QDateTime>

class Console : public QLineEdit{
    Q_OBJECT
public:
    Console();
    inline void clear(){ this->setText(""); }
signals:
    void serifReq(QString);
protected slots:
    void exec();
};

#endif // CONSOLE_H
