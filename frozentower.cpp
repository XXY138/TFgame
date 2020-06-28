#include "frozentower.h"
#include "gamewindow.h"
#include "enemy.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include<QtMath>
#include<QList>

FrozenTower::FrozenTower(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow* game,double line,double damage):
    Tower(posi,startattck,endattack,pixFileName,game,line,damage)
{

}


void FrozenTower::draw(QPainter *painter) const{
    painter->drawPixmap(_posi,_pixmap);
    painter->save();
    if(_target){
        painter->setPen(Qt::NoPen);
        painter->setPen(QPen(Qt::white,_line));     /*冰冻塔的攻击激光为白色*/
        painter->drawLine(_posi.x()+50,_posi.y()+50,_target->getCurrentPos().x()+50,_target->getCurrentPos().y()+35);
    }
    painter->restore();
}


void FrozenTower::upDateCheck(){
    if(!_target){
        QList<Enemy *> enemyList=_game->get_enemylist();
        foreach (Enemy* enemy,enemyList)
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
            _target->getFrozenAttack(this);     /*与普通塔的区别为每次检查调用的是getFrozenAttack函数而不是getAttack函数*/
    }
    }
}

void FrozenTower::chooseToAttack(Enemy *enemy)
{
    _target=enemy;
    _target->getFrozenAttack(this);     /*与普通塔的区别为每次检查调用的是getFrozenAttack函数而不是getAttack函数*/
}
