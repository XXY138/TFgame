#include "menubutton2.h"

/*菜单按钮选项数目为8个*/
MenuButton2::MenuButton2(QString pix) : QPushButton (0),_pixmap(pix)
{
    this->setFixedSize(_pixmap.width(),_pixmap.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(_pixmap);
    this->setIconSize(QSize(_pixmap.size()));
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction * action1=new QAction(this);
    action1->setText("at [1]");
    this->addAction(action1);
    connect(action1,&QAction::triggered,this,[=](){
        emit at1();
    });

    QAction * action2=new QAction(this);
    action2->setText("at [2]");
    this->addAction(action2);
    connect(action2,&QAction::triggered,this,[=](){
        emit at2();
    });

    QAction * action3=new QAction(this);
    action3->setText("at [3]");
    this->addAction(action3);
    connect(action3,&QAction::triggered,this,[=](){
        emit at3();
    });

    QAction * action4=new QAction(this);
    action4->setText("at [4]");
    this->addAction(action4);
    connect(action4,&QAction::triggered,this,[=](){
        emit at4();
    });

    QAction * action5=new QAction(this);
    action5->setText("at [5]");
    this->addAction(action5);
    connect(action5,&QAction::triggered,this,[=](){
        emit at5();
    });

    QAction * action6=new QAction(this);
    action6->setText("at [6]");
    this->addAction(action6);
    connect(action6,&QAction::triggered,this,[=](){
        emit at6();
    });

    QAction * action7=new QAction(this);
    action7->setText("at [7]");
    this->addAction(action7);
    connect(action7,&QAction::triggered,this,[=](){
        emit at7();
    });

    QAction * action8=new QAction(this);
    action8->setText("at [8]");
    this->addAction(action8);
    connect(action8,&QAction::triggered,this,[=](){
        emit at8();
    });
}
