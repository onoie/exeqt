
#include <stdlib.h>

#include "tetrixwindow.h"
#include "qxp/qxp.h"
#include "qxp/sqxp.h"
#include "slib.h"
#include "mwindow.h"

int main(int argc, char *argv[]){

    Qxp qxp;
    qDebug() << qxp.hello("qxp");
    qDebug() << Sqxp::echo("Sqxp");

    Q_INIT_RESOURCE(qxpr);
    Q_INIT_RESOURCE(resource);

    Slib::createCacheDirectory();

    QApplication app(argc, argv);

    //forRand()
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    MWindow mw;
    mw.show();
    Slib::mv(&mw,MVPosition::CENTER);

//    TetrixWindow window;
//    window.show();

    return app.exec();
}
