#ifndef FROZENTOWER_H
#define FROZENTOWER_H

#include "tower.h"

/*冰冻塔继承了塔，除了攻击的激光绘制不同、每次刷新调用的检查函数不同、选中敌人的函数不同*/
class FrozenTower:public Tower
{
public:
    FrozenTower(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow* game,double line,double damage);
    void draw(QPainter *painter) const;
    void upDateCheck();
    void chooseToAttack(Enemy* enemy);
};

#endif // FROZENTOWER_H
