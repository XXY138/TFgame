#include "tower.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>

Tower::Tower(QPoint posi,QString pixFileName):QObject (0),_pixmap(pixFileName)
{
    _posi=posi;
}

void Tower::draw(QPainter *paint){
    paint->drawPixmap(_posi,_pixmap);
}
