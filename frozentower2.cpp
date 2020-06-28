#include "frozentower2.h"
#include "gamewindow2.h"
#include "enemy2.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include<QtMath>
#include<QList>

FrozenTower2::FrozenTower2(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow2* game,double line,double damage):
    Tower2(posi,startattck,endattack,pixFileName,game,line,damage)
{

}

void FrozenTower2::draw(QPainter *painter) const{
    painter->drawPixmap(_posi,_pixmap);
    painter->save();
    if(_target){
        painter->setPen(Qt::NoPen);
        painter->setPen(QPen(Qt::white,_line));
        painter->drawLine(_posi.x()+50,_posi.y()+50,_target->getCurrentPos().x()+50,_target->getCurrentPos().y()+35);
    }
    painter->restore();
}

void FrozenTower2::upDateCheck(){
    if(!_target){
        QList<Enemy2 *> enemyList=_game->get_enemylist();
        foreach (Enemy2* enemy,enemyList)
        {
            if (enemy->getCurrentPos().x()>this->_startAttack.x() && enemy->getCurrentPos().x()<this->_endAttack.x() && enemy->isAlive())
            {
                chooseToAttack(enemy);
                break;
            }
        }
    }
    else {
        if(_target->getCurrentPos().x()>this->_endAttack.x()){
            if (_target)
                _target=NULL;


        }
    else {
            _target->getFrozenAttack(this);
    }
    }
}

void FrozenTower2::chooseToAttack(Enemy2 *enemy)
{
    _target=enemy;
    _target->getFrozenAttack(this);
}
