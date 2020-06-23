#include "menubutton.h"

MenuButton::MenuButton(QString pix) : QPushButton (0),_pixmap(pix)
{
    this->setFixedSize(_pixmap.width(),_pixmap.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(_pixmap);
    this->setIconSize(QSize(_pixmap.size()));
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction * action1=new QAction(this);
    action1->setText("Set a normal tower at [1]");
    this->addAction(action1);
    connect(action1,&QAction::triggered,this,[=](){
        emit setUp1_1();
    });

    QAction * action2=new QAction(this);
    action2->setText("Set a slowing tower at [1]");
    this->addAction(action2);
    connect(action2,&QAction::triggered,this,[=](){
        emit setUp1_2();
    });

    QAction * action3=new QAction(this);
    action3->setText("Set a normal tower at [2]");
    this->addAction(action3);
    connect(action3,&QAction::triggered,this,[=](){
        emit setUp2_1();
    });

    QAction * action4=new QAction(this);
    action4->setText("Set a slowing tower at [2]");
    this->addAction(action4);
    connect(action4,&QAction::triggered,this,[=](){
        emit setUp2_2();
    });

    QAction * action5=new QAction(this);
    action5->setText("Set a normal tower at [3]");
    this->addAction(action5);
    connect(action5,&QAction::triggered,this,[=](){
        emit setUp3_1();
    });

    QAction * action6=new QAction(this);
    action6->setText("Set a slowing tower at [3]");
    this->addAction(action6);
    connect(action6,&QAction::triggered,this,[=](){
        emit setUp3_2();
    });
}
