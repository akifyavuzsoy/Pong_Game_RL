#include "ball.h"
#include "paddle.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

Ball::Ball(qreal x, qreal y, qreal diameter)
    : QGraphicsEllipseItem(0, 0, diameter, diameter), xVelocity(BALL_VELOCITY), yVelocity(BALL_VELOCITY)
{
    setPos(x, y); // Başlangıç pozisyonunu ayarla

    // Topun rengini ayarla (örneğin, beyaz)
    setBrush(QBrush(Qt::white));
    setPen(QPen(Qt::black)); // Topun kenar rengini ayarla

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Ball::move);
    timer->start(50);
}

void Ball::move()
{
    QList<QGraphicsItem *> collidingItems = this->collidingItems();

    for (QGraphicsItem *item : collidingItems) {
        if (typeid(*item) == typeid(Paddle)) {
            xVelocity = -xVelocity;
        }
    }

    if (x() <= 0 || x() + rect().width() >= scene()->width()) {
        xVelocity = -xVelocity;
    }

    if (y() <= 0 || y() + rect().height() >= scene()->height()) {
        yVelocity = -yVelocity;
    }

    setPos(x() + xVelocity, y() + yVelocity);
}

void Ball::setXVelocity(qreal velocity)
{
    xVelocity = velocity;
}

void Ball::setYVelocity(qreal velocity)
{
    yVelocity = velocity;
}

qreal Ball::getXVelocity() const
{
    return xVelocity;
}

qreal Ball::getYVelocity() const
{
    return yVelocity;
}
