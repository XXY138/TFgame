#include "endwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QMediaPlayer>


EndWindow::EndWindow(QString filename,QWidget *parent) : QMainWindow(parent),_pixmap(filename)
{
    this->setFixedSize(1100,750);
}

void EndWindow::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),_pixmap);
}
