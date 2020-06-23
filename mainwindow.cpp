#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include "button.h"
#include "window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(1100,750);
    ui->setupUi(this);
    Button *button=new Button(":/anniu.jpeg");
    button->setParent(this);
    button->move(140,380);
    Window *scene = new Window;
    connect(button,&QPushButton::clicked,this,[=](){
        this->close();
        scene->show();
    });
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/music/mario.mp3"));
    player->setVolume(30);
    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* e){
    QPainter painter(this);
    QPixmap pixmap(":/fengmian3.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

