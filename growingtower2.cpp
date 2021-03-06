#include "growingtower2.h"
#include "gamewindow2.h"
#include "enemy2.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include<QtMath>
#include<QList>
#include<QMediaPlayer>

GrowingTower2::GrowingTower2(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow2* game,double line,double damage):
    Tower2(posi,startattck,endattack,pixFileName,game,line,damage),_killedNum(0)
{

}

void GrowingTower2::draw(QPainter *painter) const{
    painter->drawPixmap(_posi,_pixmap);
    painter->save();
    if(_target){
        painter->setPen(Qt::NoPen);
        painter->setPen(QPen(Qt::red,_line));
        painter->drawLine(_posi.x()+50,_posi.y()+50,_target->getCurrentPos().x()+50,_target->getCurrentPos().y()+35);
    }
    painter->restore();
}

void GrowingTower2::targetKilled()
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
}

