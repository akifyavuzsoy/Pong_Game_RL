#include "paddle.h"
#include <QKeyEvent>
#include <QBrush>
#include <QPen>

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height, bool isPlayer)
    : QGraphicsRectItem(0, 0, width, height), isPlayer(isPlayer), moveUpPressed(false), moveDownPressed(false)
{
    setRect(0, 0, width, height); // Dikdörtgenin boyutlarını belirle
    setPos(x, y); // Başlangıç pozisyonunu ayarla

    if (isPlayer) {
        setBrush(QBrush(Qt::blue)); // Oyuncu paddle'ının rengini ayarla
    } else {
        setBrush(QBrush(Qt::red)); // Bilgisayar paddle'ının rengini ayarla
    }
    setPen(QPen(Qt::black)); // Paddle'ların kenar rengini ayarla
}

void Paddle::keyPressEvent(QKeyEvent *event)
{
    if (isPlayer) {
        if (event->key() == Qt::Key_Up) {
            moveUpPressed = true;
        } else if (event->key() == Qt::Key_Down) {
            moveDownPressed = true;
        }
    }
}

void Paddle::keyReleaseEvent(QKeyEvent *event)
{
    if (isPlayer) {
        if (event->key() == Qt::Key_Up) {
            moveUpPressed = false;
        } else if (event->key() == Qt::Key_Down) {
            moveDownPressed = false;
        }
    }
}

void Paddle::moveUp()
{
    if (moveUpPressed && y() > 0) {
        setPos(x(), y() - 10);
    }
}

void Paddle::moveDown()
{
    if (moveDownPressed && y() + rect().height() < 600) { // 600: Scene height
        setPos(x(), y() + 10);
    }
}
