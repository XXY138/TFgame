#include "tower.h"
#include "gamewindow.h"
#include "enemy.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include<QtMath>
#include<QList>

Tower::Tower(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow* game):
    QObject (0),
    _posi(posi),
    _pixmap(pixFileName),
    _startAttack(startattck),
    _endAttack(endattack),
    _fireRate(1000),
    _damage(1),
    _game(game),
    _target(NULL)
{
    /*_fireTimer = new QTimer(this);
    connect(_fireTimer, SIGNAL(timeout()), this, SLOT(shoot()));*/
}

void Tower::draw(QPainter *painter) const{
    painter->save();
    painter->drawPixmap(_posi,_pixmap);
    painter->restore();
}

QPoint Tower::getPos(){
    return this->_posi;
}


int Tower::getDamageValue(){
    return this->_damage;
}

void Tower::upDateCheck(){
    if(!_target){
        QList<Enemy *> enemyList=_game->get_enemylist();
        foreach (Enemy* enemy,enemyList)
        {
            if (enemy->getCurrentPos().rx()>this->_startAttack.rx() && enemy->getCurrentPos().rx()<this->_endAttack.rx() && enemy->isAlive())
            {
                chooseToAttack(enemy);
                break;
            }
        }
    }
    else {
        if(_target->getCurrentPos().rx()>this->_endAttack.rx()){
            if (_target)
                _target=NULL;

            /*_fireTimer->stop();*/
        }
    else {
        _target->getAttack(this);
    }
    }
}

void Tower::chooseToAttack(Enemy *enemy)
{
    _target=enemy;
    /*attack();*/
    _target->getAttack(this);
}

/*void Tower::attack(){
    _fireTimer->start(_fireRate);
}*/

void Tower::targetKilled()
{
    if (_target)
        _target=NULL;

   /* _fireTimer->stop();*/
}

/*void Tower::loseEnemy(){

}

void Tower::enemyKilled(){
    if(_chosenEnemy)
        _chosenEnemy=NULL;
    _rateTimer->stop();
}



void Tower::attackEnemy(){
    _rateTimer->start(_rate);
}*/

