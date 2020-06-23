#include "gamewindow.h"
#include "button.h"
#include "enemy.h"
#include "menubutton.h"
#include <QPainter>
#include <QTimer>
#include <QMediaPlayer>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    _gameWin(false),
    _gameLose(false),
    _gold(1000),
    _waves(0),
    _totalWaves(3),
    _playerHp(10),
    tower1_exist(false),
    tower2_exist(false),
    tower3_exist(false)
{
    this->setFixedSize(1100,750);
    Button * backbutton = new Button(":/backbutton.jpg");
    backbutton->setParent(this);
    backbutton->move(5,5);



     /*Button * set_tower1 =new Button(":/1.jpg");
    set_tower1->setParent(this);
    set_tower1->move(1000,5);
    connect(set_tower1,&Button::clicked,this,&GameWindow::setTower1);

    Button * set_tower2 =new Button(":/2.jpg");
    set_tower2->setParent(this);
    set_tower2->move(1000,95);
    connect(set_tower2,&Button::clicked,this,&GameWindow::setTower2);

    Button * set_tower3 =new Button(":/3.jpg");
    set_tower3->setParent(this);
    set_tower3->move(1000,185);
    connect(set_tower3,&Button::clicked,this,&GameWindow::setTower3);

    Button * delete_tower1 =new Button(":/111.jpg");
    delete_tower1->setParent(this);
    delete_tower1->move(800,5);
    connect(delete_tower1,&Button::clicked,this,&GameWindow::deleteTower1);

    Button * delete_tower2 =new Button(":/222.jpg");
    delete_tower2->setParent(this);
    delete_tower2->move(800,95);
    connect(delete_tower2,&Button::clicked,this,&GameWindow::deleteTower2);

    Button * delete_tower3 =new Button(":/333.jpg");
    delete_tower3->setParent(this);
    delete_tower3->move(800,185);
    connect(delete_tower3,&Button::clicked,this,&GameWindow::deleteTower3);*/


    connect(backbutton,&Button::clicked,this,[=](){
        emit chooseToBack();
    });

    Button * set_o =new Button(":/anniu.jpeg");
    set_o->setParent(this);
    set_o->move(100,600);
    connect(set_o,&Button::clicked,this,&GameWindow::addEnemy);
    QTimer * timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&GameWindow::updateScene);
    timer->start(100);

    MenuButton *menubtn1=new MenuButton(":/set_up.png");
    menubtn1->setParent(this);
    menubtn1->move(5,100);
    connect(menubtn1,&MenuButton::setUp1_1,this,&GameWindow::setTower1_1);
    connect(menubtn1,&MenuButton::setUp1_2,this,&GameWindow::setTower1_2);
    connect(menubtn1,&MenuButton::setUp2_1,this,&GameWindow::setTower2_1);
    connect(menubtn1,&MenuButton::setUp2_2,this,&GameWindow::setTower2_2);
    connect(menubtn1,&MenuButton::setUp3_1,this,&GameWindow::setTower3_1);
    connect(menubtn1,&MenuButton::setUp3_2,this,&GameWindow::setTower3_2);
}

void GameWindow::paintEvent(QPaintEvent *){

    if(_gameWin || _gameLose){
        QString text=_gameLose?"You lose!":"You win!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::black));
        painter.drawText(rect(),Qt::AlignCenter,text);
        return;
    }

    QPainter painter(this);
    QPixmap pixmap(":/beijing4.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    foreach (const Tower *tower, _towerlist)
        tower->draw(&painter);
    foreach (const Enemy *enemy, _enemylist)
        enemy->draw(&painter);
}

void GameWindow::setTower1_1(){
    if(!tower1_exist){
        Tower * new_tower=new Tower(QPoint(195,615),QPoint(10,500),QPoint(300,500),":/trueta1.png",this);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/music/shortSetTower.mp3"));
        player->setVolume(30);
        player->play();
        _towerlist.push_back(new_tower);
        tower1_exist=true;
        update();
    }
    else {
        return;
    }
}

void GameWindow::setTower1_2(){
    if(!tower1_exist){
        Tower * new_tower=new Tower(QPoint(195,615),QPoint(10,500),QPoint(300,500),":/trueta2.png",this);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/music/shortSetTower.mp3"));
        player->setVolume(30);
        player->play();
        _towerlist.push_back(new_tower);
        tower1_exist=true;
        update();
    }
    else {
        return;
    }
}

void GameWindow::setTower2_1(){
    if(!tower2_exist){
        Tower * new_tower=new Tower(QPoint(410,410),QPoint(300,500),QPoint(700,500),":/trueta1.png",this);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/music/shortSetTower.mp3"));
        player->setVolume(30);
        player->play();
        _towerlist.push_back(new_tower);
        tower2_exist=true;
        update();
    }
    else {
        return;
    }
}

void GameWindow::setTower2_2(){
    if(!tower2_exist){
        Tower * new_tower=new Tower(QPoint(410,410),QPoint(300,500),QPoint(700,500),":/trueta2.png",this);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/music/shortSetTower.mp3"));
        player->setVolume(30);
        player->play();
        _towerlist.push_back(new_tower);
        tower2_exist=true;
        update();
    }
    else {
        return;
    }
}

void GameWindow::setTower3_1(){
    if(!tower3_exist){
        Tower * new_tower=new Tower(QPoint(660,615),QPoint(700,500),QPoint(1000,500),":/trueta1.png",this);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/music/shortSetTower.mp3"));
        player->setVolume(30);
        player->play();
        _towerlist.push_back(new_tower);
        tower3_exist=true;
        update();
    }
    else {
        return;
    }
}

void GameWindow::setTower3_2(){
    if(!tower3_exist){
        Tower * new_tower=new Tower(QPoint(660,615),QPoint(700,500),QPoint(1000,500),":/trueta2.png",this);
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/music/shortSetTower.mp3"));
        player->setVolume(30);
        player->play();
        _towerlist.push_back(new_tower);
        tower3_exist=true;
        update();
    }
    else {
        return;
    }
}



void GameWindow::deleteTower1(){
    if(tower1_exist){

    }
    else{
        return;
    }
}

void GameWindow::deleteTower2(){
    if(tower2_exist){

    }
    else{
        return;
    }
}

void GameWindow::deleteTower3(){
    if(tower3_exist){

    }
    else{
        return;
    }
}

void GameWindow::addEnemy(){
    Enemy *enemy=new Enemy(QPoint(10,500),QPoint(1000,500),":/truecrow.png");
    _enemylist.push_back(enemy);
}

void GameWindow::updateScene(){
    foreach(Enemy *enemy,this->_enemylist)
        enemy->move();
    foreach(Tower *tower,this->_towerlist)
        tower->upDateCheck();
    update();
}


void GameWindow::getHpDamage(int damage){
    _playerHp-=damage;
    if(_playerHp<=0)
        _gameLose=true;
}


void GameWindow::awardGold(int gold)
{
    _gold += gold;
    update();
}

QList<Enemy*> GameWindow::get_enemylist(){
    return this->_enemylist;
}
