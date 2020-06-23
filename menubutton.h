#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QObject>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QAction>

class MenuButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MenuButton(QString pix);

private:
    QPixmap _pixmap;

signals:
    void setUp1_1();
    void setUp1_2();
    void setUp2_1();
    void setUp2_2();
    void setUp3_1();
    void setUp3_2();

public slots:
};

#endif // MENUBUTTON_H
