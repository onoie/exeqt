
#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QFrame>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class TetrixBoard;

#include <QtWidgets>
#include "tetrixboard.h"

class TetrixWindow : public QWidget{
    Q_OBJECT
public:
    TetrixWindow(){
        board = new TetrixBoard;
        nextPieceLabel = new QLabel;
        nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
        nextPieceLabel->setAlignment(Qt::AlignCenter);
        board->setNextPieceLabel(nextPieceLabel);
        scoreLcd = new QLCDNumber(5);
        scoreLcd->setSegmentStyle(QLCDNumber::Filled);
        levelLcd = new QLCDNumber(2);
        levelLcd->setSegmentStyle(QLCDNumber::Filled);
        linesLcd = new QLCDNumber(5);
        linesLcd->setSegmentStyle(QLCDNumber::Filled);

        startButton = new QPushButton(tr("&Start"));
        startButton->setFocusPolicy(Qt::NoFocus);
        quitButton = new QPushButton(tr("&Quit"));
        quitButton->setFocusPolicy(Qt::NoFocus);
        pauseButton = new QPushButton(tr("&Pause"));
        pauseButton->setFocusPolicy(Qt::NoFocus);
        connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
        connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
        connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
        connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
        connect(board, SIGNAL(levelChanged(int)), levelLcd, SLOT(display(int)));
        connect(board, SIGNAL(linesRemovedChanged(int)),linesLcd, SLOT(display(int)));
        QGridLayout *layout = new QGridLayout;
        layout->addWidget(createLabel(tr("NEXT")), 0, 0);
        layout->addWidget(nextPieceLabel, 1, 0);
        layout->addWidget(createLabel(tr("LEVEL")), 2, 0);
        layout->addWidget(levelLcd, 3, 0);
        layout->addWidget(startButton, 4, 0);
        layout->addWidget(board, 0, 1, 6, 1);
        layout->addWidget(createLabel(tr("SCORE")), 0, 2);
        layout->addWidget(scoreLcd, 1, 2);
        layout->addWidget(createLabel(tr("LINES REMOVED")), 2, 2);
        layout->addWidget(linesLcd, 3, 2);
        layout->addWidget(quitButton, 4, 2);
        layout->addWidget(pauseButton, 5, 2);
        setLayout(layout);
        setWindowTitle(tr("Tetrix"));
        resize(550, 370);
    }
private:
    QLabel *createLabel(const QString &text){
        QLabel *lbl = new QLabel(text);
        lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
        return lbl;
    }
    TetrixBoard *board;
    QLabel *nextPieceLabel;
    QLCDNumber *scoreLcd;
    QLCDNumber *levelLcd;
    QLCDNumber *linesLcd;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;
};

#endif
