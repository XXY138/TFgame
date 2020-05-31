#include "gamewindow.h"
#include "button.h"
#include <QPainter>
#include <QTimer>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1100,750);
    Button * backbutton = new Button(":/backbutton.jpg");
    backbutton->setParent(this);
    backbutton->move(5,5);
    Button * set_tower =new Button(":/anniu.jpeg");
    set_tower->setParent(this);
    set_tower->move(300,400);
    Button * set_o =new Button(":/anniu.jpeg");
    set_o->setParent(this);
    set_o->move(100,600);
    connect(set_o,&Button::clicked,this,&GameWindow::addObject);
    connect(set_tower,&Button::clicked,this,&GameWindow::setTower);
    connect(backbutton,&Button::clicked,this,[=](){
        emit chooseToBack();
    });
    QTimer * timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&GameWindow::updateScene);
    timer->start(10);

}

void GameWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/beijing2.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    foreach(Tower * tower,_towerlist)
        tower->draw(&painter);
    foreach(Object * object,_objectlist)
        object->draw(&painter);
}

void GameWindow::setTower(){
    Tower * new_tower=new Tower(QPoint(300,300),":/ta1.png");
    _towerlist.push_back(new_tower);
    update();
}

void GameWindow::addObject(){
    Object * object=new Object(QPoint(10,500),QPoint(1000,500),":/truecrow.png");
    _objectlist.push_back(object);
    object->move();
    update();
}

void GameWindow::updateScene(){
    update();
}
