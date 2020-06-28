#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPainter>

class QPainter;
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
    void getFrozenAttack(Tower* attacker);
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
    GameWindow* _game;
};

#endif // ENEMY_H
