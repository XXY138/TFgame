#include "menubutton.h"

/*建立有三个选项的菜单按钮*/
MenuButton::MenuButton(QString pix) : QPushButton (0),_pixmap(pix)
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

    QAction * action3=new QAction(this);
    action3->setText("at [2]");
    this->addAction(action3);
    connect(action3,&QAction::triggered,this,[=](){
        emit at2();
    });

    QAction * action5=new QAction(this);
    action5->setText("at [3]");
    this->addAction(action5);
    connect(action5,&QAction::triggered,this,[=](){
        emit at3();
    });
}
