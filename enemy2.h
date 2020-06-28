#ifndef ENEMY2_H
#define ENEMY2_H


#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPainter>

class GameWindow2;
class Tower2;


/*专为GameWindow2设计的敌人类*/
class Enemy2 : public QObject
{
    Q_OBJECT
public:
    Enemy2(QString filename,GameWindow2* game,int maxHp,int damage,int value,double speed);
    void draw(QPainter *painter) const;
    void move();
    QPoint getCurrentPos();
    void getAttack(Tower2* attacker);
    void getFrozenAttack(Tower2* attacker);
    bool isAlive();
    void getDeleted();
    bool checkArrive();
    int getDamageValue();
    int getValue();

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
    GameWindow2* _game;
};

#endif // ENEMY2_H
