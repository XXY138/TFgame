#ifndef FROZENTOWER2_H
#define FROZENTOWER2_H


#include "tower2.h"

/*专为GameWindow2设计的冰冻塔类*/
class FrozenTower2:public Tower2
{
public:
    FrozenTower2(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow2* game,double line,double damage);
    void draw(QPainter *painter) const;
    void upDateCheck();
    void chooseToAttack(Enemy2* enemy);
};

#endif // FROZENTOWER2_H
