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
    Enemy(QPoint start,QPoint target,QString filename);
    void draw(QPainter *painter) const;
    void move();
    QPoint getCurrentPos();
    void getAttack(Tower* attacker);
    bool isAlive();


public slots:

private:
    bool _alive;
    int	_currentHp;
    int _maxHp;
    double _speed;
    QPoint _startpos;
    QPoint _targetpos;
    QPoint _currentpos;
    QPixmap _pixmap;
};

#endif // ENEMY_H
