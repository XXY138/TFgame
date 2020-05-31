#include "object.h"

Object::Object(QPoint start,QPoint target,QString filename):QObject (0),_pixmap(filename)
{
    this->_currentpos=start;
    this->_startpos=start;
    this->_targetpos=target;
}

void Object::draw(QPainter *painter){
    painter->drawPixmap(_currentpos,_pixmap);
}

void Object::move(){
    QPropertyAnimation *animation =new QPropertyAnimation(this,"_currentpos");
    animation->setDuration(2000);
    animation->setStartValue(_startpos);
    animation->setEndValue(_targetpos);
    animation->start();
}

QPoint Object::getCurrentPos(){
    return this->_currentpos;
}

void Object::setCurrentPos(QPoint pos){
    this->_currentpos=pos;
}
