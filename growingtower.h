#ifndef GROWINGTOWER_H
#define GROWINGTOWER_H


#include "tower.h"


class GrowingTower:public Tower
{
public:
    GrowingTower(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow* game,double line,double damage);
    void draw(QPainter *painter) const;
    void targetKilled();


private:
    int _killedNum;
};

#endif // GROWINGTOWER_H
