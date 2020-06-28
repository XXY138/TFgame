#include "tower2.h"
#include "gamewindow2.h"
#include "enemy2.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include<QtMath>
#include<QList>
#include <QMediaPlayer>

Tower2::Tower2(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow2* game,double line,double damage):
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

void Tower2::draw(QPainter *painter) const{
    painter->drawPixmap(_posi,_pixmap);
    painter->save();
    if(_target){
        painter->setPen(Qt::NoPen);
        painter->setPen(QPen(Qt::yellow,_line));
        painter->drawLine(_posi.x()+50,_posi.y()+50,_target->getCurrentPos().x()+50,_target->getCurrentPos().y()+35);
    }
    painter->restore();
}

QPoint Tower2::getPos()const{
    return this->_posi;
}


int Tower2::getDamageValue(){
    return this->_damage;
}

void Tower2::upDateCheck(){
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
        if(_target->getCurrentPos().x()>=this->_endAttack.x()){
            if (_target)
                _target=NULL;
        }
    else {
            _target->getAttack(this);
    }
    }
}

void Tower2::chooseToAttack(Enemy2 *enemy)
{
    _target=enemy;
    _target->getAttack(this);
}

void Tower2::targetKilled()
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


void Tower2::upGrade(){
    this->_damage+=1;
    this->_line+=1;
}

