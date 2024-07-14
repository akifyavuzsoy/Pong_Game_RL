#ifndef REINFORCEMENTLEARNING_H
#define REINFORCEMENTLEARNING_H

#include "paddle.h"
#include "ball.h"
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QObject>
#include <QHash>
#include <QString>

class ReinforcementLearning
{
public:
    ReinforcementLearning(Paddle *paddle);
    void update(Ball *ball);
    void penalize();
    void reward();
    void saveModel(const QString &filename);

private:
    Paddle *paddle;
    QMap<QString, double> qTable;
    double learningRate;
    double discountFactor;
    QString getState(Ball *ball);
    QString lastState;
    QString lastAction;
};

#endif // REINFORCEMENTLEARNING_H
