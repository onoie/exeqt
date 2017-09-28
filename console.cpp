#include "console.h"

Console::Console(){
    connect(this, SIGNAL(returnPressed()),this, SLOT(exec()));
}
void Console::exec(){
    qDebug()<<"input:"<<this->text();
    clear();
}

