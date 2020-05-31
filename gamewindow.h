#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "tower.h"
#include <QMainWindow>
#include <QList>
#include "object.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void setTower();
    void addObject();
    void updateScene();

private:
    QList<Tower*> _towerlist;
    QList<Object*> _objectlist;

signals:
    void chooseToBack();

public slots:
};

#endif // GAMEWINDOW_H
