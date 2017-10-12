#include "console.h"

Console::Console(){
    connect(this, SIGNAL(returnPressed()),this, SLOT(exec()));
}
void Console::exec(){
    qDebug() << "input:" << this->text();
    QString t = this->text();
    QRegExp reg("^serif:(.+)");
    if(reg.exactMatch(this->text())){
        reg.indexIn(t);
        emit serifReq(reg.cap(1));
    }
    clear();
}

