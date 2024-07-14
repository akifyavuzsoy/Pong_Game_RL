#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

class Paddle : public QGraphicsRectItem
{
public:
    Paddle(qreal x, qreal y, qreal width, qreal height, bool isPlayer);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void moveUp();
    void moveDown();

private:
    bool moveUpPressed;
    bool moveDownPressed;
    bool isPlayer;
};

#endif // PADDLE_H
