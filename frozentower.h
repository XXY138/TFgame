#ifndef FROZENTOWER_H
#define FROZENTOWER_H

#include "tower.h"


class FrozenTower:public Tower
{
public:
    FrozenTower(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow* game,double line,double damage);
    void draw(QPainter *painter) const;
    void upDateCheck();
    void chooseToAttack(Enemy* enemy);
};

#endif // FROZENTOWER_H
