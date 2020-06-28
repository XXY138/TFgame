#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include <QMediaPlayer>
#include "button.h"
#include "window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(1100,750);
    ui->setupUi(this);
    Button *button=new Button(":/start_btn.png");
    button->setParent(this);
    button->move(460,400);
    Window *scene = new Window;

    QMediaPlayer * player2 = new QMediaPlayer;
    player2->setMedia(QUrl("qrc:/music/mario.mp3"));
    player2->setVolume(30);
    player2->play();

    /*用一个Button类链接MainWindow和Window*/
    connect(button,&QPushButton::clicked,this,[=](){
        player2->stop();        /*切换界面时切换音乐*/
        this->close();
        scene->show();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    QPixmap pixmap(":/realcover.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

