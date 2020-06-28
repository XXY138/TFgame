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
    void playSound(QString music,int volume);       /*�������֣����ã���װ�ɺ�����ʹ�������ࣩ*/
    void HpRecover();               /*һ����Ѫ����Ѫ��*/
    void HpRecoverPartially();      /*���ֻ�Ѫ��һ��10�㣩*/
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
    bool _flag;             /*�������һֻ���Ƿ��Ѿ���������Ϣ*/
    int wave_num;
    bool* tower_exist;      /*�������Ƿ���ڵ���Ϣ*/
    bool* tower_frozen;     /*�������Ƿ�Ϊ����������Ϣ*/


signals:


public slots:
};

#endif // GAMEWINDOW_H
