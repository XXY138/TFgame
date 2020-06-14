#include "object2.h"
#include <QPoint>
#include <QVector2D>
#include <QPainter>


Object2::Object2(QPoint start,QPoint target,QString filename):QObject (0),_pixmap(filename)
{
    this->_currentpos=start;
    this->_startpos=start;
    this->_targetpos=target;
    this->_speed=4;
}

void Object2::move(){
    QVector2D vector(this->_targetpos-this->_startpos);
    vector.normalize();
    this->_currentpos=this->_currentpos+vector.toPoint()*this->_speed;
}

void Object2::draw(QPainter *painter){
    painter->drawPixmap(this->_currentpos,this->_pixmap);
}

QPoint Object2::getCurrentPos(){
    return this->_currentpos;
}
