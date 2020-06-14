#include "gamewindow.h"
#include "button.h"
#include "object2.h"
#include <QPainter>
#include <QTimer>


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    _waves(0),_totalWaves(3),
    _playerHp(10),
    _gold(1000),
    _gameWin(false),
    _gameLose(false),
    tower1_exist(false),
    tower2_exist(false),
    tower3_exist(false)
{
    this->setFixedSize(1100,750);
    Button * backbutton = new Button(":/backbutton.jpg");
    backbutton->setParent(this);
    backbutton->move(5,5);

    Button * set_o =new Button(":/anniu.jpeg");
    set_o->setParent(this);
    set_o->move(100,600);
    connect(set_o,&Button::clicked,this,&GameWindow::addObject);

    Button * set_tower1 =new Button(":/1.jpg");
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
    connect(delete_tower3,&Button::clicked,this,&GameWindow::deleteTower3);


    connect(backbutton,&Button::clicked,this,[=](){
        emit chooseToBack();
    });

    QTimer * timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&GameWindow::updateScene);
    timer->start(10);

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
    foreach(Tower * tower,_towerlist)
        tower->draw(&painter);
    foreach(Object2 * object,_objectlist)
        object->draw(&painter);
}

void GameWindow::setTower1(){
    if(!tower1_exist){
        Tower * new_tower=new Tower(QPoint(415,395),QPoint(300,500),QPoint(700,500),this,":/trueta2.png");
        _towerlist.push_back(new_tower);
        tower1_exist=true;
        update();
    }
    else {
        return;
    }
}

void GameWindow::setTower2(){
    if(!tower2_exist){
        Tower * new_tower=new Tower(QPoint(660,615),QPoint(700,500),QPoint(1000,500),this,":/trueta1.png");
        _towerlist.push_back(new_tower);
        update();
    }
    else {
        return;
    }
}

void GameWindow::setTower3(){
    if(!tower3_exist){
        Tower * new_tower=new Tower(QPoint(195,615),QPoint(10,500),QPoint(300,500),this,":/trueta1.png");
        _towerlist.push_back(new_tower);
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

void GameWindow::addObject(){
    Object2 * object=new Object2(QPoint(10,500),QPoint(1000,500),":/truecrow.png");
    _objectlist.push_back(object);
    object->move();
    update();
}

void GameWindow::updateScene(){
    foreach(Object2* object,this->_objectlist)
           object->move();
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


