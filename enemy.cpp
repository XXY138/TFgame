#include "enemy.h"
#include "tower.h"
#include <QPoint>
#include <QVector2D>
#include <QPainter>

static const int Hp_Width = 50;

Enemy::Enemy(QPoint start,QPoint target,QString filename):
    QObject (0),
    _alive(true),
    _currentHp(100),
    _maxHp(100),
    _speed(4),
    _startpos(start),
    _targetpos(target),
    _currentpos(start),
    _pixmap(filename)
{

}

void Enemy::move(){
    QVector2D vector(this->_targetpos-this->_startpos);
    vector.normalize();
    this->_currentpos=this->_currentpos+vector.toPoint()*this->_speed;
}

void Enemy::draw(QPainter *painter) const{
    painter->drawPixmap(this->_currentpos,this->_pixmap);
    painter->save();

    QPoint HpBarPoint = _currentpos + QPoint(Hp_Width/2, 0);
    // »æÖÆÑªÌõ
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect HpBarBackRect(HpBarPoint, QSize(Hp_Width, 5));
    painter->drawRect(HpBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(HpBarPoint, QSize((double)_currentHp / _maxHp * Hp_Width, 5));
    painter->drawRect(healthBarRect);
}

QPoint Enemy::getCurrentPos(){
    return this->_currentpos;
}

void Enemy::getAttack(Tower* attacker){
    int damage=attacker->getDamageValue();
    if(this->_currentHp-damage>0)
        this->_currentHp=this->_currentHp-damage;
    else {
        this->_currentHp=0;
        this->_alive=false;
        attacker->targetKilled();
    }
}

bool Enemy::isAlive(){
    return this->_alive;
}
