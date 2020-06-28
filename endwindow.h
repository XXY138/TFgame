#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>

class EndWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EndWindow(QString filename,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* e);

private:
    QPixmap _pixmap;

signals:

public slots:
};

#endif // ENDWINDOW_H
