#ifndef GAMEWINDOW2_H
#define GAMEWINDOW2_H


#include "tower2.h"
#include <QMainWindow>
#include <QList>
#include <QMediaPlayer>

/*第二关和第一关有许多功能相似但是又有许多不同，故新创了一个类*/
/*别的带2系列的类都是专为GameWindow2定做的*/

class Enemy2;

class GameWindow2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow2(QWidget *parent = nullptr);
    ~GameWindow2();
    void paintEvent(QPaintEvent*);
    void updateScene();
    void addEnemy(QString filename,GameWindow2* game,int maxHp,int damage,int value,double speed);
    void deleteEnemy(Enemy2* enemy);
    void setTower(QPoint pos,QPoint start,QPoint end,QString pix,int type);
    void upGradeTower(QPoint pos);
    void deleteTower(QPoint pos);
    void getHpDamage(int damage);
    void awardGold(int gold);
    void showGold_Hp(QPainter* painter);       /*播放音乐（常用，封装成函数以使代码更简洁）*/
    void playSound(QString music,int volume);
    void HpRecover();               /*一键回血（满血）*/
    void HpRecoverPartially();          /*部分回血（一次10点）*/
    QList<Enemy2*> get_enemylist();
    QMediaPlayer* _player;
    QTimer* _timer;
    QTimer* _enemytimer1;


protected:
    bool _gameWin;
    bool _gameLose;
    int _gold;
    int _playerHp;
    QList<Tower2*> _towerlist;
    QList<Enemy2*> _enemylist;
    bool _flag;             /*储存最后一只怪是否已经出来的信息*/
    int wave_num;
    bool* tower_exist;      /*储存塔是否存在的信息*/
    bool* tower_frozen;     /*储存塔是否为冰冻塔的信息*/

signals:


public slots:
};
#endif // GAMEWINDOW2_H
