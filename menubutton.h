#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QAction>


/*菜单按钮，游戏界面中的重要部件*/
class MenuButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MenuButton(QString pix);

private:
    QPixmap _pixmap;

signals:
    void at1();
    void at2();
    void at3();

public slots:
};

#endif // MENUBUTTON_H
