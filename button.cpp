#include "button.h"
#include <QPixmap>

Button::Button(QString pix) : QPushButton(0)
{
    /*���һ��������ͼƬ�����СΪ��С�İ�ť*/
    QPixmap pixmap(pix);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}
