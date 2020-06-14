#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(QString pix);
    Button();

signals:

public slots:
};

#endif // BUTTON_H
