#include "gamewindow2.h"
#include "button.h"
#include "enemy2.h"
#include "menubutton2.h"
#include "frozentower2.h"
#include "growingtower2.h"
#include "endwindow.h"
#include <QPainter>
#include <QTimer>
#include <QMediaPlayer>
#include <stdlib.h>

static const int normal_cost=150;
static const int frozen_cost=300;
static const int growing_cost=300;
static const int upgrade_cost=200;
static const int total_num=30;
static const QPoint Pos1(28,615);
static const QPoint Pos2(139,370);
static const QPoint Pos3(273,615);
static const QPoint Pos4(398,370);
static const QPoint Pos5(518,615);
static const QPoint Pos6(644,370);
static const QPoint Pos7(763,615);
static const QPoint Pos8(896,370);
static const QPoint start_pos(0,475);
static const QPoint end_pos(944,475);

GameWindow2::GameWindow2(QWidget *parent) :
    QMainWindow(parent),
    _gameWin(false),
    _gameLose(false),
    _gold(1200),
    _playerHp(100),
    _flag(false),
    wave_num(0)
{
    tower_exist=new bool(false);
    tower_frozen=new bool(false);

    _timer=new QTimer(this);
    connect(_timer,&QTimer::timeout,this,&GameWindow2::updateScene);

    _enemytimer1=new QTimer(this);
    /*使每次定时器被触发的时候都根据已出的怪物的个数来出不同的怪，实现仅用一个定时器出不同的怪，并且当波数到达某预设值后开始多个怪物一起出*/
    connect(_enemytimer1,&QTimer::timeout,this,[=](){
        if(wave_num<=5){
            addEnemy(":/vil8.png",this,180,10,100,4);
            wave_num+=1;
        }
        else if (wave_num<=10) {
            addEnemy(":/vil6.png",this,200,15,125,4.5);
            wave_num+=1;
        }
        else if(wave_num<=total_num){
            switch (wave_num%5)
            {
            case 0:{
                addEnemy(":/vil1.png",this,180,20,150,4);
                addEnemy(":/vil4.png",this,140,20,150,5.5);
                break;
            }
            case 1:{
                addEnemy(":/vil2.png",this,200,20,150,3.5);
                addEnemy(":/vil4.png",this,140,20,150,5.5);
                break;
            }
            case 2:{
                addEnemy(":/vil3.png",this,160,20,150,5);
                addEnemy(":/vil2.png",this,200,20,150,3.5);
                break;
            }
            case 3:{
                addEnemy(":/vil4.png",this,140,20,150,5.5);
                addEnemy(":/vil1.png",this,180,20,150,4);
                break;
            }
            case 4:{
                addEnemy(":/vil7.png",this,220,20,150,3);
                addEnemy(":/vil4.png",this,140,20,150,5.5);
                break;
            }
            }
            wave_num+=2;
        }
        else {
            addEnemy(":/big22.png",this,1200,100,1000,1.5);
            _flag=true;
            _enemytimer1->stop();
        }
    });

    _player=new QMediaPlayer;
    _player->setMedia(QUrl("qrc:/music/mountains.mp3"));
    _player->setVolume(30);

    this->setFixedSize(1100,750);


    /*设定两个回血键*/
    Button *hpbtn=new Button(":/b55.png");
    hpbtn->setParent(this);
    hpbtn->move(305,130);
    connect(hpbtn,&Button::clicked,this,&GameWindow2::HpRecover);

    Button *hppbtn=new Button(":/b66.png");
    hppbtn->setParent(this);
    hppbtn->move(475,130);
    connect(hppbtn,&Button::clicked,this,&GameWindow2::HpRecoverPartially);

    /*设定三个建塔键，一个升级键，一个删除键*/
    MenuButton2 *menubtn1=new MenuButton2(":/b11.png");
    menubtn1->setParent(this);
    menubtn1->move(50,50);
    connect(menubtn1,&MenuButton2::at1,this,[=](){
        setTower(Pos1,start_pos,QPoint(118,500),":/castle1.png",1);
    });
    connect(menubtn1,&MenuButton2::at2,this,[=](){
        setTower(Pos2,QPoint(118,500),QPoint(236,500),":/castle1.png",1);
    });
    connect(menubtn1,&MenuButton2::at3,this,[=](){
        setTower(Pos3,QPoint(236,500),QPoint(354,500),":/castle1.png",1);
    });
    connect(menubtn1,&MenuButton2::at4,this,[=](){
        setTower(Pos4,QPoint(354,500),QPoint(472,500),":/castle1.png",1);
    });
    connect(menubtn1,&MenuButton2::at5,this,[=](){
        setTower(Pos5,QPoint(472,500),QPoint(590,500),":/castle1.png",1);
    });
    connect(menubtn1,&MenuButton2::at6,this,[=](){
        setTower(Pos6,QPoint(590,500),QPoint(708,500),":/castle1.png",1);
    });
    connect(menubtn1,&MenuButton2::at7,this,[=](){
        setTower(Pos7,QPoint(708,500),QPoint(826,500),":/castle1.png",1);
    });
    connect(menubtn1,&MenuButton2::at8,this,[=](){
        setTower(Pos8,QPoint(826,500),end_pos,":/castle1.png",1);
    });

    MenuButton2 *menubtn2=new MenuButton2(":/b22.png");
    menubtn2->setParent(this);
    menubtn2->move(220,50);
    connect(menubtn2,&MenuButton2::at1,this,[=](){
        setTower(Pos1,start_pos,QPoint(118,500),":/castle2.png",2);
    });
    connect(menubtn2,&MenuButton2::at2,this,[=](){
        setTower(Pos2,QPoint(118,500),QPoint(236,500),":/castle2.png",2);
    });
    connect(menubtn2,&MenuButton2::at3,this,[=](){
        setTower(Pos3,QPoint(236,500),QPoint(354,500),":/castle2.png",2);
    });
    connect(menubtn2,&MenuButton2::at4,this,[=](){
        setTower(Pos4,QPoint(354,500),QPoint(472,500),":/castle2.png",2);
    });
    connect(menubtn2,&MenuButton2::at5,this,[=](){
        setTower(Pos5,QPoint(472,500),QPoint(590,500),":/castle2.png",2);
    });
    connect(menubtn2,&MenuButton2::at6,this,[=](){
        setTower(Pos6,QPoint(590,500),QPoint(708,500),":/castle2.png",2);
    });
    connect(menubtn2,&MenuButton2::at7,this,[=](){
        setTower(Pos7,QPoint(708,500),QPoint(826,500),":/castle2.png",2);
    });
    connect(menubtn2,&MenuButton2::at8,this,[=](){
        setTower(Pos8,QPoint(826,500),end_pos,":/castle2.png",2);
    });

    MenuButton2 *menubtn5=new MenuButton2(":/b88.png");
    menubtn5->setParent(this);
    menubtn5->move(390,50);
    connect(menubtn5,&MenuButton2::at1,this,[=](){
        setTower(Pos1,start_pos,QPoint(118,500),":/castle3.png",3);
    });
    connect(menubtn5,&MenuButton2::at2,this,[=](){
        setTower(Pos2,QPoint(118,500),QPoint(236,500),":/castle3.png",3);
    });
    connect(menubtn5,&MenuButton2::at3,this,[=](){
        setTower(Pos3,QPoint(236,500),QPoint(354,500),":/castle3.png",3);
    });
    connect(menubtn5,&MenuButton2::at4,this,[=](){
        setTower(Pos4,QPoint(354,500),QPoint(472,500),":/castle3.png",3);
    });
    connect(menubtn5,&MenuButton2::at5,this,[=](){
        setTower(Pos5,QPoint(472,500),QPoint(590,500),":/castle3.png",3);
    });
    connect(menubtn5,&MenuButton2::at6,this,[=](){
        setTower(Pos6,QPoint(590,500),QPoint(708,500),":/castle3.png",3);
    });
    connect(menubtn5,&MenuButton2::at7,this,[=](){
        setTower(Pos7,QPoint(708,500),QPoint(826,500),":/castle3.png",3);
    });
    connect(menubtn5,&MenuButton2::at8,this,[=](){
        setTower(Pos8,QPoint(826,500),end_pos,":/castle3.png",3);
    });

    MenuButton2 *menubtn3=new MenuButton2(":/b33.png");
    menubtn3->setParent(this);
    menubtn3->move(560,50);
    connect(menubtn3,&MenuButton2::at1,this,[=](){
        upGradeTower(Pos1);
    });
    connect(menubtn3,&MenuButton2::at2,this,[=](){
        upGradeTower(Pos2);
    });
    connect(menubtn3,&MenuButton2::at3,this,[=](){
        upGradeTower(Pos3);
    });
    connect(menubtn3,&MenuButton2::at4,this,[=](){
        upGradeTower(Pos4);
    });
    connect(menubtn3,&MenuButton2::at5,this,[=](){
        upGradeTower(Pos5);
    });
    connect(menubtn3,&MenuButton2::at6,this,[=](){
        upGradeTower(Pos6);
    });
    connect(menubtn3,&MenuButton2::at7,this,[=](){
        upGradeTower(Pos7);
    });
    connect(menubtn3,&MenuButton2::at8,this,[=](){
        upGradeTower(Pos8);
    });


    MenuButton2 *menubtn4=new MenuButton2(":/b44.png");
    menubtn4->setParent(this);
    menubtn4->move(730,50);
    connect(menubtn4,&MenuButton2::at1,this,[=](){
        deleteTower(Pos1);
    });
    connect(menubtn4,&MenuButton2::at2,this,[=](){
        deleteTower(Pos2);
    });
    connect(menubtn4,&MenuButton2::at3,this,[=](){
        deleteTower(Pos3);
    });
    connect(menubtn4,&MenuButton2::at4,this,[=](){
        deleteTower(Pos4);
    });
    connect(menubtn4,&MenuButton2::at5,this,[=](){
        deleteTower(Pos5);
    });
    connect(menubtn4,&MenuButton2::at6,this,[=](){
        deleteTower(Pos6);
    });
    connect(menubtn4,&MenuButton2::at7,this,[=](){
        deleteTower(Pos7);
    });
    connect(menubtn4,&MenuButton2::at8,this,[=](){
        deleteTower(Pos8);
    });

}


GameWindow2::~GameWindow2(){
    delete tower_exist;
    tower_exist=NULL;
    delete tower_frozen;
    tower_frozen=NULL;
    delete _timer;
    _timer=NULL;
    delete _player;
    _player=NULL;
    delete _enemytimer1;
}

void GameWindow2::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/p2.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    showGold_Hp(&painter);

    foreach (const Tower2 *tower, _towerlist)
        tower->draw(&painter);
    foreach (const Enemy2 *enemy, _enemylist)
        enemy->draw(&painter);
}

void GameWindow2::updateScene(){
    /*失血过多则输*/
    if(_playerHp<=0){
        _timer->stop();
        _player->stop();
        this->close();
        playSound("qrc:/music/showyourself.mp3",30);
        EndWindow* end=new EndWindow(":/fail.jpg");
        end->show();
    }
    else {
        /*如果最后一个怪也出来了并且怪物列表已空，则赢*/
        if (_flag && _enemylist.empty()){
            _timer->stop();
            _player->stop();
            this->close();
            playSound("qrc:/music/epi.mp3",30);
            EndWindow* end=new EndWindow(":win.jpg");
            end->show();
        }

        /*不输也不赢则继续刷新*/
        foreach(Enemy2 *enemy,this->_enemylist){
            if(!enemy->checkArrive())
                enemy->move();
            else {
                this->getHpDamage(enemy->getDamageValue());
                this->deleteEnemy(enemy);
            }
        }
        foreach(Tower2 *tower,this->_towerlist){
            tower->upDateCheck();
        }
        update();
    }

}


void GameWindow2::addEnemy(QString filename,GameWindow2* game,int maxHp,int damage,int value,double speed){
    Enemy2 *enemy=new Enemy2(filename,game,maxHp,damage,value,speed);
    _enemylist.push_back(enemy);
}

void GameWindow2::deleteEnemy(Enemy2* enemy){
    _enemylist.removeOne(enemy);
    delete enemy;
}

/*有八个建塔位置，每个位置有三种可能*/
void GameWindow2::setTower(QPoint pos, QPoint start, QPoint end, QString pix,int type){
    if(pos==Pos1){
        if(!tower_exist[0] && _gold>=normal_cost){
            if(type==1){
                Tower2 * new_tower=new Tower2(Pos1,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[0]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower2 * new_tower=new FrozenTower2(Pos1,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[0]=true;
                    tower_exist[0]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower2 * new_tower=new GrowingTower2(Pos1,start,end,pix,this,2.5,2);
                    _towerlist.push_back(new_tower);
                    _gold-=growing_cost;
                    tower_exist[0]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
        }
    }

    else if (pos==Pos2) {
        if(!tower_exist[1] && _gold>=normal_cost){
            if(type==1){
                Tower2 * new_tower=new Tower2(Pos2,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[1]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower2 * new_tower=new FrozenTower2(Pos2,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[1]=true;
                    tower_exist[1]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower2 * new_tower=new GrowingTower2(Pos2,start,end,pix,this,2.5,2);
                    _towerlist.push_back(new_tower);
                    _gold-=growing_cost;
                    tower_exist[1]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
        }
    }

    else if(pos==Pos3) {
        if(!tower_exist[2] && _gold>=normal_cost){
            if(type==1){
                Tower2 * new_tower=new Tower2(Pos3,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[2]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower2 * new_tower=new FrozenTower2(Pos3,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[2]=true;
                    tower_exist[2]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower2 * new_tower=new GrowingTower2(Pos3,start,end,pix,this,2.5,2);
                    _towerlist.push_back(new_tower);
                    _gold-=growing_cost;
                    tower_exist[2]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
        }
    }

    else if (pos==Pos4) {
        if(!tower_exist[3] && _gold>=normal_cost){
            if(type==1){
                Tower2 * new_tower=new Tower2(Pos4,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[3]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower2 * new_tower=new FrozenTower2(Pos4,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[3]=true;
                    tower_exist[3]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower2 * new_tower=new GrowingTower2(Pos4,start,end,pix,this,2.5,2);
                    _towerlist.push_back(new_tower);
                    _gold-=growing_cost;
                    tower_exist[3]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
        }
    }

    else if (pos==Pos5) {
        if(!tower_exist[4] && _gold>=normal_cost){
            if(type==1){
                Tower2 * new_tower=new Tower2(Pos5,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[4]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower2 * new_tower=new FrozenTower2(Pos5,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[4]=true;
                    tower_exist[4]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower2 * new_tower=new GrowingTower2(Pos5,start,end,pix,this,2.5,2);
                    _towerlist.push_back(new_tower);
                    _gold-=growing_cost;
                    tower_exist[4]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
        }
    }

    else if (pos==Pos6) {
        if(!tower_exist[5] && _gold>=normal_cost){
            if(type==1){
                Tower2 * new_tower=new Tower2(Pos6,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[5]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower2 * new_tower=new FrozenTower2(Pos6,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[5]=true;
                    tower_exist[5]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower2 * new_tower=new GrowingTower2(Pos6,start,end,pix,this,2.5,2);
                    _towerlist.push_back(new_tower);
                    _gold-=growing_cost;
                    tower_exist[5]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
        }
    }

    else if (pos==Pos7) {
        if(!tower_exist[6] && _gold>=normal_cost){
            if(type==1){
                Tower2 * new_tower=new Tower2(Pos7,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[6]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower2 * new_tower=new FrozenTower2(Pos7,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[6]=true;
                    tower_exist[6]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower2 * new_tower=new GrowingTower2(Pos7,start,end,pix,this,2.5,2);
                    _towerlist.push_back(new_tower);
                    _gold-=growing_cost;
                    tower_exist[6]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
        }
    }

    else if (pos==Pos8) {
        if(!tower_exist[7] && _gold>=normal_cost){
            if(type==1){
                Tower2 * new_tower=new Tower2(Pos8,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[7]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower2 * new_tower=new FrozenTower2(Pos8,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[7]=true;
                    tower_exist[7]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower2 * new_tower=new GrowingTower2(Pos8,start,end,pix,this,2.5,2);
                    _towerlist.push_back(new_tower);
                    _gold-=growing_cost;
                    tower_exist[7]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
        }
    }
}

void GameWindow2::upGradeTower(QPoint pos){
    if(_gold>=upgrade_cost){
        foreach(Tower2* tower,_towerlist){

            if(tower->getPos().x()==pos.x()){
                playSound("qrc:/music/upgrade.mp3",30);

                tower->upGrade();
                _gold-=upgrade_cost;

                break;
            }
        }
    }
    else {
        return;
    }
}

void GameWindow2::deleteTower(QPoint pos){
    foreach(Tower2* tower,_towerlist){

        if(tower->getPos()==pos){
            _towerlist.removeOne(tower);
            delete tower;

            /*拆塔后要把标签重新初始化*/
            if(pos==Pos1){
                tower_exist[0]=false;
                tower_frozen[0]=false;
            }
            else if (pos==Pos2) {
                tower_exist[1]=false;
                tower_frozen[1]=false;
            }
            else if (pos==Pos3) {
                tower_exist[2]=false;
                tower_frozen[2]=false;
            }
            else if (pos==Pos4) {
                tower_exist[3]=false;
                tower_frozen[3]=false;
            }
            else if (pos==Pos5) {
                tower_exist[4]=false;
                tower_frozen[4]=false;
            }
            else if (pos==Pos6) {
                tower_exist[5]=false;
                tower_frozen[5]=false;
            }
            else if (pos==Pos7) {
                tower_exist[6]=false;
                tower_frozen[6]=false;
            }
            else if (pos==Pos8) {
                tower_exist[7]=false;
                tower_frozen[7]=false;
            }



            playSound("qrc:/music/enemy.mp3",20);

            break;
        }
    }
}



void GameWindow2::getHpDamage(int damage){
    _playerHp-=damage;

    playSound("qrc:/music/Hp.mp3",30);

    if(_playerHp<=0)
        _gameLose=true;
}


void GameWindow2::awardGold(int gold)
{
    _gold += gold;
}

void GameWindow2::showGold_Hp(QPainter *painter){
    QFont font("宋体",25,QFont::Bold,false);
    painter->save();
    painter->setFont(font);
    painter->setPen(QPen(Qt::white,3));

    /*结构化输出金币和玩家血量*/
    painter->drawText(QRect(100,10,250,150),QString("Gold:%1").arg(_gold));
    painter->drawText(QRect(995,604,250,150),QString("Hp:%1").arg(_playerHp));

    painter->restore();
}

void GameWindow2::playSound(QString music,int volume){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl(music));
    player->setVolume(volume);
    player->play();
}

void GameWindow2::HpRecover(){
    if(_gold>=500){
        if(_playerHp<100){
            playSound("qrc:/music/upgrade.mp3",30);
            _playerHp=100;
            _gold-=500;
            return;
        }
    }
}

void GameWindow2::HpRecoverPartially(){
    if(_gold>=100){
        if(_playerHp+10<=100){
            playSound("qrc:/music/upgrade.mp3",30);
            _playerHp+=10;
            _gold-=100;
            return;
        }
        else if (_playerHp<100) {
            playSound("qrc:/music/upgrade.mp3",30);
            _playerHp=100;
            _gold-=100;
            return;
        }
    }
}


QList<Enemy2*> GameWindow2::get_enemylist(){
    return this->_enemylist;
}
