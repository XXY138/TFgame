#ifndef GROWINGTOWER2_H
#define GROWINGTOWER2_H


#include "tower2.h"


/*专为GameWindow2设计的自我成长塔类*/
class GrowingTower2:public Tower2
{
public:
    GrowingTower2(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow2* game,double line,double damage);
    void draw(QPainter *painter) const;
    void targetKilled();


private:
    int _killedNum;
};

#endif // GROWINGTOWER2_H
