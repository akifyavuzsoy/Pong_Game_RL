#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>

#define BALL_VELOCITY 8

class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball(qreal x, qreal y, qreal diameter);
    void setXVelocity(qreal velocity);
    void setYVelocity(qreal velocity);

    qreal getXVelocity() const;
    qreal getYVelocity() const;

public slots:
    void move();

private:
    qreal xVelocity;
    qreal yVelocity;
};

#endif // BALL_H
