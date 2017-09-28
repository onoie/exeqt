#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QLineEdit>
#include <QDebug>

class Console : public QLineEdit{
    Q_OBJECT
public:
    Console();
    inline void clear(){ this->setText(""); }
protected slots:
    void exec();
};

#endif // CONSOLE_H
