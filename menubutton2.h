#ifndef MENUBUTTON2_H
#define MENUBUTTON2_H


#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QAction>

class MenuButton2 : public QPushButton
{
    Q_OBJECT
public:
    explicit MenuButton2(QString pix);

private:
    QPixmap _pixmap;

signals:
    void at1();
    void at2();
    void at3();
    void at4();
    void at5();
    void at6();
    void at7();
    void at8();

public slots:
};

#endif // MENUBUTTON2_H
