
#ifndef TETRIXPIECE_H
#define TETRIXPIECE_H

#include <QtCore>
#include <stdlib.h>

enum TetrixShape {
    NoShape, ZShape, SShape, LineShape,
    TShape, SquareShape,LShape, MirroredLShape
};

class TetrixPiece{
public:
    TetrixPiece() { setShape(NoShape); }
    void setRandomShape(){
        setShape(TetrixShape(qrand() % 7 + 1));
    }
    void setShape(TetrixShape shape){
        static const int coordsTable[8][4][2] = {
            { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
            { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
            { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
            { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
            { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
            { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
            { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
            { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
        };
        for (int i = 0; i < 4 ; i++) {
            for (int j = 0; j < 2; ++j)
                coords[i][j] = coordsTable[shape][i][j];
        }
        pieceShape = shape;
    }
    TetrixShape shape() const { return pieceShape; }
    int x(int index) const { return coords[index][0]; }
    int y(int index) const { return coords[index][1]; }
    int minX() const{
        int min = coords[0][0];
        for (int i = 1; i < 4; ++i)
            min = qMin(min, coords[i][0]);
        return min;
    }
    int maxX() const{
        int max = coords[0][0];
        for (int i = 1; i < 4; ++i)
            max = qMax(max, coords[i][0]);
        return max;
    }
    int minY() const{
        int min = coords[0][1];
        for (int i = 1; i < 4; ++i)
            min = qMin(min, coords[i][1]);
        return min;
    }
    int maxY() const{
        int max = coords[0][1];
        for (int i = 1; i < 4; ++i)
            max = qMax(max, coords[i][1]);
        return max;
    }
    TetrixPiece rotatedLeft() const{
        if (pieceShape == SquareShape){
            return *this;
        }
        TetrixPiece result;
        result.pieceShape = pieceShape;
        for (int i = 0; i < 4; ++i) {
            result.setX(i, y(i));
            result.setY(i, -x(i));
        }
        return result;
    }
    TetrixPiece rotatedRight() const{
        if (pieceShape == SquareShape){
            return *this;
        }
        TetrixPiece result;
        result.pieceShape = pieceShape;
        for (int i = 0; i < 4; ++i) {
            result.setX(i, -y(i));
            result.setY(i, x(i));
        }
        return result;
    }
private:
    void setX(int index, int x) { coords[index][0] = x; }
    void setY(int index, int y) { coords[index][1] = y; }
    TetrixShape pieceShape;
    int coords[4][2];
};

#endif
