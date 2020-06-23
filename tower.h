#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QTimer>

class Enemy;
class GameWindow;
class Bullet;

class Tower : public QObject
{
    Q_OBJECT
public:
    explicit Tower(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow* game);
    void draw(QPainter *paint) const;
    QPoint getPos();
    int getDamageValue();
    void upDateCheck();
    void chooseToAttack(Enemy* enemy);
    void attack();
    void targetKilled();

private:
    QPoint _posi;
    QPixmap _pixmap;
    QPoint _startAttack;
    QPoint _endAttack;
    int _fireRate;
    int _damage;
    Enemy* _target;
    GameWindow* _game;
    /*QTimer * _fireTimer;*/

signals:

private slots:
    /*void shoot();*/
};

#endif // TOWER_H
