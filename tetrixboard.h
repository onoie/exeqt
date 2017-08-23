
#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H

#include <QtWidgets>
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include "tetrixpiece.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class TetrixBoard : public QFrame{
    Q_OBJECT
public:
    TetrixBoard(QWidget *parent = 0): QFrame(parent){
        setFrameStyle(QFrame::Panel | QFrame::Sunken);
        setFocusPolicy(Qt::StrongFocus);
        isStarted = false;
        isPaused = false;
        clearBoard();
        nextPiece.setRandomShape();
    }
    void setNextPieceLabel(QLabel *label){
        nextPieceLabel = label;
    }
    QSize sizeHint() const override{
        return QSize(BoardWidth * 15 + frameWidth() * 2,BoardHeight * 15 + frameWidth() * 2);
    }
    QSize minimumSizeHint() const override{
        return QSize(BoardWidth * 5 + frameWidth() * 2,BoardHeight * 5 + frameWidth() * 2);
    }
public slots:
    void start(){
        if (isPaused){return;}
        isStarted = true;
        isWaitingAfterLine = false;
        numLinesRemoved = 0;
        numPiecesDropped = 0;
        score = 0;
        level = 1;
        clearBoard();
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);
        emit levelChanged(level);
        newPiece();
        timer.start(timeoutTime(), this);
    }
    void pause(){
        if (!isStarted){return;}
        isPaused = !isPaused;
        if (isPaused) {
            timer.stop();
        } else {
            timer.start(timeoutTime(), this);
        }
        update();
    }
signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);
protected:
    void paintEvent(QPaintEvent *event) override{
        QFrame::paintEvent(event);
        QPainter painter(this);
        QRect rect = contentsRect();
        if (isPaused) {
            painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
            return;
        }
        int boardTop = rect.bottom() - BoardHeight*squareHeight();
        for (int i = 0; i < BoardHeight; ++i) {
            for (int j = 0; j < BoardWidth; ++j) {
                TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
                if (shape != NoShape)
                    drawSquare(painter, rect.left() + j * squareWidth(),
                               boardTop + i * squareHeight(), shape);
            }
        }
        if (curPiece.shape() != NoShape) {
            for (int i = 0; i < 4; ++i) {
                int x = curX + curPiece.x(i);
                int y = curY - curPiece.y(i);
                drawSquare(painter, rect.left() + x * squareWidth(),
                           boardTop + (BoardHeight - y - 1) * squareHeight(),
                           curPiece.shape());
            }
        }
    }
    void keyPressEvent(QKeyEvent *event) override{
        if (!isStarted || isPaused || curPiece.shape() == NoShape) {
            QFrame::keyPressEvent(event);
            return;
        }
        switch (event->key()) {
        case Qt::Key_Left:
            tryMove(curPiece, curX - 1, curY);
            break;
        case Qt::Key_Right:
            tryMove(curPiece, curX + 1, curY);
            break;
        case Qt::Key_Down:
            tryMove(curPiece.rotatedRight(), curX, curY);
            break;
        case Qt::Key_Up:
            tryMove(curPiece.rotatedLeft(), curX, curY);
            break;
        case Qt::Key_Space:
            dropDown();
            break;
        case Qt::Key_D:
            oneLineDown();
            break;
        default:
            QFrame::keyPressEvent(event);
        }
    }
    void timerEvent(QTimerEvent *event) override{
        if (event->timerId() == timer.timerId()) {
            if (isWaitingAfterLine) {
                isWaitingAfterLine = false;
                newPiece();
                timer.start(timeoutTime(), this);
            } else {
                oneLineDown();
            }
        } else {
            QFrame::timerEvent(event);
        }
    }
private:
    enum { BoardWidth = 10, BoardHeight = 22 };
    TetrixShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
    int timeoutTime() { return 1000 / (1 + level); }
    int squareWidth() { return contentsRect().width() / BoardWidth; }
    int squareHeight() { return contentsRect().height() / BoardHeight; }
    void clearBoard(){
        for (int i = 0; i < BoardHeight * BoardWidth; ++i)
            board[i] = NoShape;
    }
    void dropDown(){
        int dropHeight = 0;
        int newY = curY;
        while (newY > 0) {
            if (!tryMove(curPiece, curX, newY - 1))
                break;
            --newY;
            ++dropHeight;
        }
        pieceDropped(dropHeight);
    }
    void oneLineDown(){
        if (!tryMove(curPiece, curX, curY - 1))
            pieceDropped(0);
    }
    void pieceDropped(int dropHeight){
        for (int i = 0; i < 4; ++i) {
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            shapeAt(x, y) = curPiece.shape();
        }
        ++numPiecesDropped;
        if (numPiecesDropped % 25 == 0) {
            ++level;
            timer.start(timeoutTime(), this);
            emit levelChanged(level);
        }
        score += dropHeight + 7;
        emit scoreChanged(score);
        removeFullLines();
        if (!isWaitingAfterLine){
            newPiece();
        }
    }
    void removeFullLines(){
        int numFullLines = 0;
        for (int i = BoardHeight - 1; i >= 0; --i) {
            bool lineIsFull = true;
            for (int j = 0; j < BoardWidth; ++j) {
                if (shapeAt(j, i) == NoShape) {
                    lineIsFull = false;
                    break;
                }
            }
            if (lineIsFull) {
                ++numFullLines;
                for (int k = i; k < BoardHeight - 1; ++k) {
                    for (int j = 0; j < BoardWidth; ++j)
                        shapeAt(j, k) = shapeAt(j, k + 1);
                }
                for (int j = 0; j < BoardWidth; ++j){
                    shapeAt(j, BoardHeight - 1) = NoShape;
                }
            }
        }
        if (numFullLines > 0) {
            numLinesRemoved += numFullLines;
            score += 10 * numFullLines;
            emit linesRemovedChanged(numLinesRemoved);
            emit scoreChanged(score);
            timer.start(500, this);
            isWaitingAfterLine = true;
            curPiece.setShape(NoShape);
            update();
        }
    }
    void newPiece(){
        curPiece = nextPiece;
        nextPiece.setRandomShape();
        showNextPiece();
        curX = BoardWidth / 2 + 1;
        curY = BoardHeight - 1 + curPiece.minY();

        if (!tryMove(curPiece, curX, curY)) {
            curPiece.setShape(NoShape);
            timer.stop();
            isStarted = false;
        }
    }
    void showNextPiece(){
        if (!nextPieceLabel){return;}
        int dx = nextPiece.maxX() - nextPiece.minX() + 1;
        int dy = nextPiece.maxY() - nextPiece.minY() + 1;
        QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
        QPainter painter(&pixmap);
        painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());
        for (int i = 0; i < 4; ++i) {
            int x = nextPiece.x(i) - nextPiece.minX();
            int y = nextPiece.y(i) - nextPiece.minY();
            drawSquare(painter, x * squareWidth(), y * squareHeight(),
                       nextPiece.shape());
        }
        nextPieceLabel->setPixmap(pixmap);
    }
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY){
        for (int i = 0; i < 4; ++i) {
            int x = newX + newPiece.x(i);
            int y = newY - newPiece.y(i);
            if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight){return false;}
            if (shapeAt(x, y) != NoShape){return false;}
        }
        curPiece = newPiece;
        curX = newX;
        curY = newY;
        update();
        return true;
    }
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape){
        static const QRgb colorTable[8] = {
            0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
            0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
        };
        QColor color = colorTable[int(shape)];
        painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,color);
        painter.setPen(color.light());
        painter.drawLine(x, y + squareHeight() - 1, x, y);
        painter.drawLine(x, y, x + squareWidth() - 1, y);
        painter.setPen(color.dark());
        painter.drawLine(x + 1, y + squareHeight() - 1, x + squareWidth() - 1, y + squareHeight() - 1);
        painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1, x + squareWidth() - 1, y + 1);
    }
    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    TetrixPiece curPiece;
    TetrixPiece nextPiece;
    int curX;
    int curY;
    int numLinesRemoved;
    int numPiecesDropped;
    int score;
    int level;
    TetrixShape board[BoardWidth * BoardHeight];
};

#endif
