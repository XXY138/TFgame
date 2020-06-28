#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPainter>

class GameWindow;
class Tower;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(QString filename,GameWindow* game,int maxHp,int damage,int value,double speed);
    void draw(QPainter *painter) const;
    void move();
    QPoint getCurrentPos();
    void getAttack(Tower* attacker);
    void getFrozenAttack(Tower* attacker);      /*接受冰冻塔攻击*/
    bool isAlive();
    void getDeleted();
    bool checkArrive();                         /*判断敌人是否到达终点*/
    int getDamageValue();                       /*返回敌人的伤害值*/
    int getValue();                             /*返回敌人的金币值*/

public slots:

private:
    bool _alive;
    int	_currentHp;
    int _maxHp;
    int _damage;
    int _value;
    double _speed;
    QPoint _startpos;
    QPoint _targetpos;
    QPoint _currentpos;
    QPixmap _pixmap;
    GameWindow* _game;
};

#endif // ENEMY_H
