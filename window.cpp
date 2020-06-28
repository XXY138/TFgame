#include "window.h"
#include "button.h"
#include "gamewindow.h"
#include"gamewindow2.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1100,750);

    /*�ð�ť����Window��GameWindow*/
    Button *button1=new Button(":/guanqia1.jpg");
    button1->setParent(this);
    button1->move(400,150);
    GameWindow * scene1 = new GameWindow;
    connect(button1,&QPushButton::clicked,this,[=](){
        this->close();
        scene1->show();
        scene1->_player->play();
        scene1->_timer->start(100);
        scene1->_enemytimer1->start(7000);      /*ʹ�õ����ť�����һ�ص�ʱ�򴥷���ʱ�������￪ʼ���֣�ʵ���Զ�����*/
    });

    /*�ð�ť����Window��GameWindow2*/
    Button *button2=new Button(":/guanqia2.jpg");
    button2->setParent(this);
    button2->move(600,150);
    GameWindow2 * scene2 = new GameWindow2;
    connect(button2,&QPushButton::clicked,this,[=](){
        this->close();
        scene2->show();
        scene2->_player->play();
        scene2->_timer->start(100);
        scene2->_enemytimer1->start(5500);      /*ʹ�õ����ť����ڶ��ص�ʱ�򴥷���ʱ�������￪ʼ���֣�ʵ���Զ�����*/
    });


}

void Window::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    QPixmap pixmap(":/beijing3.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
