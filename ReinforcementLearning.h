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

#define REWARD_GAIN 5
#define PENALTY_GAIN 20
#define N_POINT_THRESHOLD -40
#define P_POINT_THRESHOLD 200

class ReinforcementLearning
{
public:
    ReinforcementLearning(Paddle *paddle);
    void update(Ball *ball);
    void penalize();
    void reward();
    void saveModel(const QString &filename);

    uint8_t rl_Reset_F;

private:
    Paddle *paddle;
    QMap<QString, double> qTable;
    double learningRate;
    double discountFactor;
    QString getState(Ball *ball);
    QString lastState;
    QString lastAction;

    int Point;
    int rewardPoints;
    int penaltyPoints;
    const int rewardThreshold = 100;
    const int penaltyThreshold = -100;
    void rl_reset();
};

#endif // REINFORCEMENTLEARNING_H
