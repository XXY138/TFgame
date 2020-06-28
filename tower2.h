#ifndef TOWER2_H
#define TOWER2_H


#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QTimer>

class Enemy2;
class GameWindow2;


/*专为GameWindow2设计的塔类*/
class Tower2 : public QObject
{
    Q_OBJECT
public:
    explicit Tower2(QPoint posi,QPoint startattck,QPoint endattack,QString pixFileName,GameWindow2* game,double line,double damage);
    QPoint getPos() const;
    int getDamageValue();
    void upGrade();
    virtual void draw(QPainter *painter) const;
    virtual void upDateCheck();
    virtual void chooseToAttack(Enemy2* enemy);
    virtual void targetKilled();

protected:
    QPoint _posi;
    QPixmap _pixmap;
    QPoint _startAttack;
    QPoint _endAttack;
    double _damage;
    double _line;
    Enemy2* _target;
    GameWindow2* _game;

signals:

private slots:

};

#endif // TOWER2_H
