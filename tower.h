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
    explicit Tower(QPoint posi,QPoint startattck,QPoint endattack,GameWindow * game,QString pixFileName);
    ~Tower();
    void draw(QPainter *paint);
    void chooseEnemy(Enemy* enemy);
    void loseEnemy();
    void attackEnemy();
    void enemyKilled();

private:
    QPoint _posi;
    QPixmap _pixmap;
    QPoint _startAttack;
    QPoint _endAttack;
    GameWindow* _game;
    QTimer* _rateTimer;
    Enemy* _chosenEnemy;
    int _rate;
    int _damage;

signals:

private slots:

};

#endif // TOWER_H
