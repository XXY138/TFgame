#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QPropertyAnimation>
#include <QPoint>
#include <QPixmap>
#include <QPainter>

class Object : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint _currentpos READ getCurrentPos WRITE setCurrentPos)
public:
    Object(QPoint start,QPoint target,QString filename);
    void draw(QPainter *painter);
    void move();
    QPoint getCurrentPos();
    void setCurrentPos(QPoint pos);
private:
    QPoint _startpos;
    QPoint _targetpos;
    QPoint _currentpos;
    QPixmap _pixmap;

signals:

public slots:
};

#endif // OBJECT_H
