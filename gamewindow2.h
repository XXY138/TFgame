#ifndef GAMEWINDOW2_H
#define GAMEWINDOW2_H


#include "tower2.h"
#include <QMainWindow>
#include <QList>
#include <QMediaPlayer>

/*�ڶ��غ͵�һ������๦�����Ƶ���������಻ͬ�����´���һ����*/
/*��Ĵ�2ϵ�е��඼��רΪGameWindow2������*/

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
    void showGold_Hp(QPainter* painter);       /*�������֣����ã���װ�ɺ�����ʹ�������ࣩ*/
    void playSound(QString music,int volume);
    void HpRecover();               /*һ����Ѫ����Ѫ��*/
    void HpRecoverPartially();          /*���ֻ�Ѫ��һ��10�㣩*/
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
    bool _flag;             /*�������һֻ���Ƿ��Ѿ���������Ϣ*/
    int wave_num;
    bool* tower_exist;      /*�������Ƿ���ڵ���Ϣ*/
    bool* tower_frozen;     /*�������Ƿ�Ϊ����������Ϣ*/

signals:


public slots:
};
#endif // GAMEWINDOW2_H
