#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "tower.h"
#include <QMainWindow>
#include <QList>


class Bullet;
class Enemy;

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void addEnemy();
    void updateScene();
    void setTower1_1();
    void setTower1_2();
    void setTower2_1();
    void setTower2_2();
    void setTower3_1();
    void setTower3_2();
    void deleteTower1();
    void deleteTower2();
    void deleteTower3();
    void getHpDamage(int damage);
    void awardGold(int gold);
    QList<Enemy*> get_enemylist();

private:
    bool _gameWin;
    bool _gameLose;
    int _gold;
    int _waves;
    int _totalWaves;
    int _playerHp;
    QList<Tower*> _towerlist;
    QList<Enemy*> _enemylist;
    bool tower1_exist;
    bool tower2_exist;
    bool tower3_exist;

signals:
    void chooseToBack();

public slots:
};

#endif // GAMEWINDOW_H
