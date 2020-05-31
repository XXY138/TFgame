#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>

class Tower : public QObject
{
    Q_OBJECT
public:
    explicit Tower(QPoint posi,QString pixFileName);
    void draw(QPainter *paint);

private:
    QPoint _posi;
    QPixmap _pixmap;

signals:

public slots:
};

#endif // TOWER_H
