#ifndef OBJECT2_H
#define OBJECT2_H

#include <QObject>
#include <QPropertyAnimation>
#include <QPoint>
#include <QPixmap>
#include <QPainter>

class Object2 : public QObject
{
    Q_OBJECT
public:
    Object2(QPoint start,QPoint target,QString filename);
    void draw(QPainter *painter);
    void move();
    QPoint getCurrentPos();

private:
    QPoint _startpos;
    QPoint _targetpos;
    QPoint _currentpos;
    QPixmap _pixmap;
    double _speed;

signals:

public slots:
};

#endif // OBJECT2_H
