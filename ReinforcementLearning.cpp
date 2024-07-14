#include "ReinforcementLearning.h"
#include <QRandomGenerator>

/**
*
*
**/

ReinforcementLearning::ReinforcementLearning(Paddle *paddle)
    : paddle(paddle), learningRate(0.1), discountFactor(0.9), lastState(""), lastAction("")
{
}

void ReinforcementLearning::update(Ball *ball)
{
    QString state = getState(ball);
    QString action = (QRandomGenerator::global()->bounded(2) == 0) ? "up" : "down";

    if (qTable.contains(state + action)) {
        qTable[state + action] += learningRate * (qTable[lastState + lastAction] + discountFactor * qTable[state + action] - qTable[lastState + lastAction]);
    } else {
        qTable[state + action] = 0.0;
    }

    if (action == "up") {
        paddle->setPos(paddle->x(), paddle->y() - 7); // Yukarı hareket
    } else {
        paddle->setPos(paddle->x(), paddle->y() + 7); // Aşağı hareket
    }

    lastState = state;
    lastAction = action;
}

void ReinforcementLearning::penalize()
{
    if (qTable.contains(lastState + lastAction)) {
        qTable[lastState + lastAction] -= learningRate;
    }
}

void ReinforcementLearning::reward()
{
    if (qTable.contains(lastState + lastAction)) {
        qTable[lastState + lastAction] += learningRate;
    }
}

void ReinforcementLearning::saveModel(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        for (auto it = qTable.begin(); it != qTable.end(); ++it) {
            out << it.key() << " " << it.value() << "\n";
        }
        file.close();
    }
}

QString ReinforcementLearning::getState(Ball *ball)
{
    return QString::number(static_cast<int>(ball->x() / 10)) + "_" + QString::number(static_cast<int>(ball->y() / 10)) + "_" + QString::number(static_cast<int>(ball->getXVelocity() / 10)) + "_" + QString::number(static_cast<int>(ball->getYVelocity() / 10));
}
