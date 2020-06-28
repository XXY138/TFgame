#include "growingtower.h"
#include "gamewindow.h"
#include "enemy.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include<QtMath>
#include<QList>
#include<QMediaPlayer>

GrowingTower::GrowingTower(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow* game,double line,double damage):
    Tower(posi,startattck,endattack,pixFileName,game,line,damage),_killedNum(0)
{

}

void GrowingTower::draw(QPainter *painter) const{
    painter->drawPixmap(_posi,_pixmap);
    painter->save();
    if(_target){
        painter->setPen(Qt::NoPen);
        painter->setPen(QPen(Qt::red,_line));
        painter->drawLine(_posi.x()+50,_posi.y()+50,_target->getCurrentPos().x()+50,_target->getCurrentPos().y()+35);
    }
    painter->restore();
}

void GrowingTower::targetKilled()
{
    if (_target){
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/music/die.mp3"));
        player->setVolume(10);
        player->play();

        _killedNum+=1;
        if(_killedNum%3==0){
            upGrade();
            QMediaPlayer * player = new QMediaPlayer;
            player->setMedia(QUrl("qrc:/music/upgrade.mp3"));
            player->setVolume(40);
            player->play();
        }

        _game->awardGold(_target->getValue());
        _target=NULL;
    }

   /* _fireTimer->stop();*/
}
