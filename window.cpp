#include "window.h"
#include "button.h"
#include "gamewindow.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1100,750);

    Button *button1=new Button(":/guanqia1.jpg");
    button1->setParent(this);
    button1->move(400,150);
    GameWindow *scene1 = new GameWindow;
    connect(button1,&QPushButton::clicked,this,[=](){
        this->close();
        scene1->show();
    });
    connect(scene1,&GameWindow::chooseToBack,this,[=](){
        scene1->close();
        this->show();
    });

    Button *button2=new Button(":/guanqia2.jpg");
    button2->setParent(this);
    button2->move(600,150);
    GameWindow *scene2 = new GameWindow;
    connect(button2,&QPushButton::clicked,this,[=](){
        this->close();
        scene2->show();
    });
    connect(scene2,&GameWindow::chooseToBack,this,[=](){
        scene2->close();
        this->show();
    });

}

void Window::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    QPixmap pixmap(":/beijing3.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
