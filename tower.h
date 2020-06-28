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
    int getDamageValue();       /*返回塔的伤害值*/
    void upGrade();
    virtual void draw(QPainter *painter) const;
    virtual void upDateCheck();             /*每次刷新页面的时候调用的函数，用于选择敌人及攻击敌人*/
    virtual void chooseToAttack(Enemy* enemy);      /*选中敌人*/
    virtual void targetKilled();        /*移除已杀死的敌人目标*/

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
