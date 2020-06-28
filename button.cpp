#include "button.h"
#include <QPixmap>

Button::Button(QString pix) : QPushButton(0)
{
    /*设计一个可以以图片自身大小为大小的按钮*/
    QPixmap pixmap(pix);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}
