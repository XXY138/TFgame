#include "gamewindow.h"
#include "button.h"
#include "enemy.h"
#include "menubutton.h"
#include "frozentower.h"
#include "growingtower.h"
#include "endwindow.h"
#include <QPainter>
#include <QTimer>
#include <QMediaPlayer>
#include <stdlib.h>

static const int normal_cost=150;
static const int frozen_cost=300;
static const int growing_cost=300;
static const int upgrade_cost=200;
static const int total_num=15;
static const QPoint Pos1(195,615);
static const QPoint Pos2(414,410);
static const QPoint Pos3(660,615);
static const QPoint start_pos(0,500);
static const QPoint end_pos(930,500);

GameWindow::GameWindow(QWidget *parent) :
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
    connect(_timer,&QTimer::timeout,this,&GameWindow::updateScene);

    _enemytimer1=new QTimer(this);
    connect(_enemytimer1,&QTimer::timeout,this,[=](){
        if(wave_num<=5){
            addEnemy(":/vil3.png",this,150,10,100,5);
            wave_num+=1;
        }
        else if (wave_num<=10) {
            addEnemy(":/vil2.png",this,150,15,125,5.5);
            wave_num+=1;
        }
        else if (wave_num<=total_num) {
            addEnemy(":/vil1.png",this,180,20,150,5);
            wave_num+=1;
        }
        else {
            addEnemy(":/big11.png",this,500,100,500,2);
            _flag=true;
            _enemytimer1->stop();
        }
    });

    _player=new QMediaPlayer;
    _player->setMedia(QUrl("qrc:/music/mountains.mp3"));
    _player->setVolume(30);

    this->setFixedSize(1100,750);


    Button *hpbtn=new Button(":/b55.png");
    hpbtn->setParent(this);
    hpbtn->move(305,130);
    connect(hpbtn,&Button::clicked,this,&GameWindow::HpRecover);

    Button *hppbtn=new Button(":/b66.png");
    hppbtn->setParent(this);
    hppbtn->move(475,130);
    connect(hppbtn,&Button::clicked,this,&GameWindow::HpRecoverPartially);



    MenuButton *menubtn1=new MenuButton(":/b11.png");
    menubtn1->setParent(this);
    menubtn1->move(50,50);
    connect(menubtn1,&MenuButton::at1,this,[=](){
        setTower(Pos1,start_pos,QPoint(310,500),":/castle1.png",1);
    });
    connect(menubtn1,&MenuButton::at2,this,[=](){
        setTower(Pos2,QPoint(310,500),QPoint(620,500),":/castle1.png",1);
    });
    connect(menubtn1,&MenuButton::at3,this,[=](){
        setTower(Pos3,QPoint(620,500),end_pos,":/castle1.png",1);
    });

    MenuButton *menubtn2=new MenuButton(":/b22.png");
    menubtn2->setParent(this);
    menubtn2->move(220,50);
    connect(menubtn2,&MenuButton::at1,this,[=](){
        setTower(Pos1,start_pos,QPoint(310,500),":/castle2.png",2);
    });
    connect(menubtn2,&MenuButton::at2,this,[=](){
        setTower(Pos2,QPoint(310,500),QPoint(620,500),":/castle2.png",2);
    });
    connect(menubtn2,&MenuButton::at3,this,[=](){
        setTower(Pos3,QPoint(620,500),end_pos,":/castle2.png",2);
    });

    MenuButton *menubtn5=new MenuButton(":/b88.png");
    menubtn5->setParent(this);
    menubtn5->move(390,50);
    connect(menubtn5,&MenuButton::at1,this,[=](){
        setTower(Pos1,start_pos,QPoint(310,500),":/castle3.png",3);
    });
    connect(menubtn5,&MenuButton::at2,this,[=](){
        setTower(Pos2,QPoint(310,500),QPoint(620,500),":/castle3.png",3);
    });
    connect(menubtn5,&MenuButton::at3,this,[=](){
        setTower(Pos3,QPoint(620,500),end_pos,":/castle3.png",3);
    });

    MenuButton *menubtn3=new MenuButton(":/b33.png");
    menubtn3->setParent(this);
    menubtn3->move(560,50);
    connect(menubtn3,&MenuButton::at1,this,[=](){
        upGradeTower(Pos1);
    });
    connect(menubtn3,&MenuButton::at2,this,[=](){
        upGradeTower(Pos2);
    });
    connect(menubtn3,&MenuButton::at3,this,[=](){
        upGradeTower(Pos3);
    });

    MenuButton *menubtn4=new MenuButton(":/b44.png");
    menubtn4->setParent(this);
    menubtn4->move(730,50);
    connect(menubtn4,&MenuButton::at1,this,[=](){
        deleteTower(Pos1);
    });
    connect(menubtn4,&MenuButton::at2,this,[=](){
        deleteTower(Pos2);
    });
    connect(menubtn4,&MenuButton::at3,this,[=](){
        deleteTower(Pos3);
    });


}

GameWindow::~GameWindow(){
    delete tower_exist;
    tower_exist=NULL;
    delete tower_frozen;
    tower_frozen=NULL;

    delete _timer;
    _timer=NULL;
    delete _player;
    _player=NULL;
}

void GameWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/p1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    showGold_Hp(&painter);

    foreach (const Tower *tower, _towerlist)
        tower->draw(&painter);
    foreach (const Enemy *enemy, _enemylist)
        enemy->draw(&painter);
}

void GameWindow::updateScene(){
    if(_playerHp<=0){
        _timer->stop();
        _player->stop();
        this->close();
        playSound("qrc:/music/showyourself.mp3",30);
        EndWindow* end=new EndWindow(":/fail.jpg");
        end->show();
    }
    else {
        if (_flag && _enemylist.empty()){
            _timer->stop();
            _player->stop();
            this->close();
            playSound("qrc:/music/epi.mp3",30);
            EndWindow* end=new EndWindow(":win.jpg");
            end->show();
        }


        foreach(Enemy *enemy,this->_enemylist){
            if(!enemy->checkArrive())
                enemy->move();
            else {
                this->getHpDamage(enemy->getDamageValue());
                this->deleteEnemy(enemy);
            }
        }
        foreach(Tower *tower,this->_towerlist){
            tower->upDateCheck();
        }
        update();
    }

}


void GameWindow::addEnemy(QString filename,GameWindow* game,int maxHp,int damage,int value,double speed){
    Enemy *enemy=new Enemy(filename,game,maxHp,damage,value,speed);
    _enemylist.push_back(enemy);
}

void GameWindow::addEnemyRandomly(){
    srand((unsigned)time(NULL));
    int num=rand()%5;
    switch (num) {
    case 0:{Enemy *enemy=new Enemy(":/vil4.png",this,80,10,100,5.5);_enemylist.push_back(enemy);break;}
    case 1:{Enemy *enemy=new Enemy(":/vil3.png",this,130,10,100,3.5);_enemylist.push_back(enemy);break;}

    case 2:{Enemy *enemy=new Enemy(":/vil2.png",this,100,15,150,5);_enemylist.push_back(enemy);break;}
    case 3:{Enemy *enemy=new Enemy(":/vil1.png",this,160,15,150,3);_enemylist.push_back(enemy);break;}

    case 4:{Enemy *enemy=new Enemy(":/vil7.png",this,140,20,200,5);_enemylist.push_back(enemy);break;}
    }
}

void GameWindow::deleteEnemy(Enemy* enemy){
    _enemylist.removeOne(enemy);
    delete enemy;
}

void GameWindow::setTower(QPoint pos, QPoint start, QPoint end, QString pix,int type){
    if(pos==Pos1){
        if(!tower_exist[0] && _gold>=normal_cost){
            if(type==1){
                Tower * new_tower=new Tower(Pos1,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[0]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower * new_tower=new FrozenTower(Pos1,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[0]=true;
                    tower_exist[0]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower * new_tower=new GrowingTower(Pos1,start,end,pix,this,2.5,2);
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
                Tower * new_tower=new Tower(Pos2,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[1]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower * new_tower=new FrozenTower(Pos2,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[1]=true;
                    tower_exist[1]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower * new_tower=new GrowingTower(Pos2,start,end,pix,this,2.5,2);
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
                Tower * new_tower=new Tower(Pos3,start,end,pix,this,1.5,1);
                _towerlist.push_back(new_tower);
                _gold-=normal_cost;
                tower_exist[2]=true;
                playSound("qrc:/music/shortSetTower.mp3",30);
            }
            else if(type==2){
                if(_gold>=frozen_cost){
                    FrozenTower * new_tower=new FrozenTower(Pos3,start,end,pix,this,1.5,1);
                    _towerlist.push_back(new_tower);
                    _gold-=frozen_cost;
                    tower_frozen[2]=true;
                    tower_exist[2]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
            else{
                if(_gold>=growing_cost){
                    GrowingTower * new_tower=new GrowingTower(Pos3,start,end,pix,this,2.5,2);
                    _towerlist.push_back(new_tower);
                    _gold-=growing_cost;
                    tower_exist[2]=true;
                    playSound("qrc:/music/shortSetTower.mp3",30);
                }
            }
        }
    }
}

void GameWindow::upGradeTower(QPoint pos){
    if(_gold>=upgrade_cost){
        foreach(Tower* tower,_towerlist){

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

void GameWindow::deleteTower(QPoint pos){
    foreach(Tower* tower,_towerlist){

        if(tower->getPos()==pos){
            _towerlist.removeOne(tower);
            delete tower;

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

            playSound("qrc:/music/enemy.mp3",20);

            break;
        }
    }
}



void GameWindow::getHpDamage(int damage){
    _playerHp-=damage;

    playSound("qrc:/music/Hp.mp3",30);

    if(_playerHp<=0)
        _gameLose=true;
}


void GameWindow::awardGold(int gold)
{
    _gold += gold;
}

void GameWindow::showGold_Hp(QPainter *painter){
    QFont font("ËÎÌו",25,QFont::Bold,false);
    painter->save();
    painter->setFont(font);
    painter->setPen(QPen(Qt::white,3));
    painter->drawText(QRect(100,10,250,150),QString("Gold:%1").arg(_gold));
    painter->drawText(QRect(995,400,250,150),QString("Hp:%1").arg(_playerHp));
    painter->restore();
}

void GameWindow::playSound(QString music,int volume){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl(music));
    player->setVolume(volume);
    player->play();
}

void GameWindow::HpRecover(){
    if(_gold>=500){
        if(_playerHp<100){
            playSound("qrc:/music/upgrade.mp3",30);
            _playerHp=100;
            _gold-=500;
            return;
        }
    }
}

void GameWindow::HpRecoverPartially(){
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


QList<Enemy*> GameWindow::get_enemylist(){
    return this->_enemylist;
}

