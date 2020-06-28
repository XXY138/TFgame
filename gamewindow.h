#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "tower.h"
#include <QMainWindow>
#include <QList>
#include <QMediaPlayer>


class Enemy;

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void paintEvent(QPaintEvent*);
    void updateScene();
    void addEnemy(QString filename,GameWindow* game,int maxHp,int damage,int value,double speed);
    void deleteEnemy(Enemy* enemy);
    void setTower(QPoint pos,QPoint start,QPoint end,QString pix,int type);
    void upGradeTower(QPoint pos);
    void deleteTower(QPoint pos);
    void getHpDamage(int damage);
    void awardGold(int gold);
    void showGold_Hp(QPainter* painter);
    void playSound(QString music,int volume);       /*播放音乐（常用，封装成函数以使代码更简洁）*/
    void HpRecover();               /*一键回血（满血）*/
    void HpRecoverPartially();      /*部分回血（一次10点）*/
    QList<Enemy*> get_enemylist();
    QMediaPlayer* _player;
    QTimer* _timer;
    QTimer* _enemytimer1;


protected:
    bool _gameWin;
    bool _gameLose;
    int _gold;
    int _playerHp;
    QList<Tower*> _towerlist;
    QList<Enemy*> _enemylist;
    bool _flag;             /*储存最后一只怪是否已经出来的信息*/
    int wave_num;
    bool* tower_exist;      /*储存塔是否存在的信息*/
    bool* tower_frozen;     /*储存塔是否为冰冻塔的信息*/


signals:


public slots:
};

#endif // GAMEWINDOW_H
