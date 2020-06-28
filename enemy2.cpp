#include "enemy2.h"
#include "tower2.h"
#include "gamewindow2.h"
#include <QPoint>
#include <QVector2D>
#include <QPainter>

static const int Hp_Width = 50;
static const QPoint start_pos(0,475);
static const QPoint end_pos(944,475);

Enemy2::Enemy2(QString filename,GameWindow2* game,int maxHp,int damage,int value,double speed):
    QObject (0),
    _alive(true),
    _currentHp(maxHp),
    _maxHp(maxHp),
    _damage(damage),
    _value(value),
    _speed(speed),
    _startpos(start_pos),
    _targetpos(end_pos),
    _currentpos(start_pos),
    _pixmap(filename),
    _game(game)
{

}

void Enemy2::move(){
    QVector2D vector(this->_targetpos-this->_startpos);
    vector.normalize();
    this->_currentpos=this->_currentpos+vector.toPoint()*this->_speed;
}

void Enemy2::draw(QPainter *painter) const{
    painter->drawPixmap(this->_currentpos,this->_pixmap);
    painter->save();

    // »æÖÆÑªÌõ
    QPoint HpBarPoint = _currentpos + QPoint(Hp_Width/2, 0);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect HpBarBackRect(HpBarPoint, QSize(Hp_Width, 5));
    painter->drawRect(HpBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(HpBarPoint, QSize((double)_currentHp / _maxHp * Hp_Width, 5));
    painter->drawRect(healthBarRect);
}

QPoint Enemy2::getCurrentPos(){
    return this->_currentpos;
}

void Enemy2::getAttack(Tower2* attacker){
    int damage=attacker->getDamageValue();
    if(this->_currentHp-damage>0)
        this->_currentHp=this->_currentHp-damage;
    else {
        this->_currentHp=0;
        this->_alive=false;
        attacker->targetKilled();
        getDeleted();
    }
}

void Enemy2::getFrozenAttack(Tower2 *attacker){
    int damage=attacker->getDamageValue();
    if(this->_currentHp-damage>0){
        if(this->_maxHp>=500)
            this->_currentHp=this->_currentHp-damage;
        else {
            this->_speed=0;
            this->_currentHp=this->_currentHp-damage;
        }
    }
    else {
        this->_currentHp=0;
        this->_alive=false;
        attacker->targetKilled();
        getDeleted();
    }
}

bool Enemy2::isAlive(){
    return this->_alive;
}

void Enemy2::getDeleted(){
    _game->deleteEnemy(this);
}

bool Enemy2::checkArrive(){
    if(_currentpos.x()>=_targetpos.x())
        return true;
    else {
        return false;
    }
}

int Enemy2::getDamageValue(){
    return this->_damage;
}

int Enemy2::getValue(){
    return this->_value;
}

