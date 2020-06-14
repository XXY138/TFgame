#include "tower.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include<QtMath>
#include<QList>

Tower::Tower(QPoint posi,QPoint startattck,QPoint endattack,GameWindow* game,QString pixFileName):QObject (0),_game(game),_pixmap(pixFileName),_posi(posi),_startAttack(startattck),_endAttack(endattack),_rate(1000),_damage(20)
{
    _rateTimer=new QTimer(this);
    connect(_rateTimer,SIGNAL(timeout()),this,SLOT(shootFire()));
}

void Tower::draw(QPainter *painter){
    painter->save();
    painter->drawPixmap(_posi,_pixmap);
    painter->restore();
}

Tower::~Tower(){
    delete _rateTimer;
    _rateTimer=NULL;
}


void Tower::loseEnemy(){

}

void Tower::enemyKilled(){
    if(_chosenEnemy)
        _chosenEnemy=NULL;
    _rateTimer->stop();
}



void Tower::attackEnemy(){
    _rateTimer->start(_rate);
}

