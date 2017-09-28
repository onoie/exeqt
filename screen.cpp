#include "screen.h"

Screen::Screen(QWidget *parent) : QWidget(parent){
    loadImage(":/lena.bmp");
    resize(500,500);
}
Screen::~Screen(){}
