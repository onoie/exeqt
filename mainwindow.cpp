
#include <QVBoxLayout>
#include <QFrame>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){


    QFrame *frame = new QFrame;
    frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    frame->setFocusPolicy(Qt::StrongFocus);
    layout()->addWidget(frame);

}
