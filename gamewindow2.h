#ifndef GAMEWINDOW2_H
#define GAMEWINDOW2_H


#include "tower2.h"
#include <QMainWindow>
#include <QList>
#include <QMediaPlayer>


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
    void addEnemyRandomly();
    void deleteEnemy(Enemy2* enemy);
    void setTower(QPoint pos,QPoint start,QPoint end,QString pix,int type);
    void upGradeTower(QPoint pos);
    void deleteTower(QPoint pos);
    void getHpDamage(int damage);
    void awardGold(int gold);
    void showGold_Hp(QPainter* painter);
    void playSound(QString music,int volume);
    void HpRecover();
    void HpRecoverPartially();
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
    bool _flag;
    int wave_num;
    bool* tower_exist;
    bool* tower_frozen;

signals:


public slots:
};
#endif // GAMEWINDOW2_H
