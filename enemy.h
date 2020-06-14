#ifndef ENEMY_H
#define ENEMY_H

#include "object2.h"
#include <QObject>
#include <QPoint>
#include <QPixmap>

class QPainter;
class GameWindow;
class Tower;

class Enemy : public Object2
{
    Q_OBJECT
public:
    Enemy(GameWindow *game, const QPixmap &sprite = QPixmap(":/truecamel.png"));
    ~Enemy();

    void getDamage(int damage);
    void getRemoved();
    void gotLostSight(Tower *attacker);
    QPoint pos() const;

public slots:

private:
    bool			_active;
    int				_maxHp;
    int				_currentHp;
    double			_speed;

    QPoint			_pos;
    GameWindow *	_game;
};

#endif // ENEMY_H
