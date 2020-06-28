#include "tower.h"
#include "gamewindow.h"
#include "enemy.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include<QtMath>
#include<QList>
#include <QMediaPlayer>

Tower::Tower(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow* game,double line,double damage):
    QObject (0),
    _posi(posi),
    _pixmap(pixFileName),
    _startAttack(startattck),
    _endAttack(endattack),
    _damage(damage),
    _line(line),
    _target(NULL),
    _game(game)
{

}

void Tower::draw(QPainter *painter) const{
    painter->drawPixmap(_posi,_pixmap);
    painter->save();
    if(_target){

        /*实时绘制塔与选中敌人之间的线，作为攻击的“激光”*/
        painter->setPen(Qt::NoPen);
        painter->setPen(QPen(Qt::yellow,_line));
        painter->drawLine(_posi.x()+50,_posi.y()+50,_target->getCurrentPos().x()+50,_target->getCurrentPos().y()+35);
    }
    painter->restore();
}

QPoint Tower::getPos()const{
    return this->_posi;
}


int Tower::getDamageValue(){
    return this->_damage;
}

void Tower::upDateCheck(){

    /*若无目标，则选择目标*/
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

    /*若有目标且在范围内则攻击，超出范围则删除目标寻找下一个*/
    else {
        if(_target->getCurrentPos().x()>=this->_endAttack.x()){
            if (_target)
                _target=NULL;
        }
    else {
            _target->getAttack(this);
    }
    }
}

void Tower::chooseToAttack(Enemy *enemy)
{
    _target=enemy;
    _target->getAttack(this);
}

void Tower::targetKilled()
{
    if (_target){
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/music/die.mp3"));
        player->setVolume(15);
        player->play();

        _game->awardGold(_target->getValue());
        _target=NULL;
    }
}


void Tower::upGrade(){
    this->_damage+=1;
    this->_line+=1;
}

