#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QTimer>

class Enemy;
class GameWindow;

class Tower : public QObject
{
    Q_OBJECT
public:
    explicit Tower(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow* game,double line,double damage);
    QPoint getPos() const;
    int getDamageValue();
    void upGrade();
    virtual void draw(QPainter *painter) const;
    virtual void upDateCheck();
    virtual void chooseToAttack(Enemy* enemy);
    virtual void targetKilled();

protected:
    QPoint _posi;
    QPixmap _pixmap;
    QPoint _startAttack;
    QPoint _endAttack;
    double _damage;
    double _line;
    Enemy* _target;
    GameWindow* _game;

signals:

private slots:

};

#endif // TOWER_H
