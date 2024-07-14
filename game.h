#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>
#include "paddle.h"
#include "ball.h"
#include "ReinforcementLearning.h"

#define MAJOR_VERSION 01
#define MINOR_VERSION 02

#define PADDLE_VELOCITY 8
#define GRAPHICS_WIDTH 750
#define GRAPHICS_HEIGHT 550
#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 100
#define SPACE 5
#define BALL_DIAMETER 20

//#define TEST_GAME
#define TRAIN_GAME

QT_BEGIN_NAMESPACE
namespace Ui {
class game;
}
QT_END_NAMESPACE

class game : public QDialog
{
    Q_OBJECT

public:
    game(QWidget *parent = nullptr);
    ~game();

private:
    Ui::game *ui;
    QGraphicsScene *scene;
    Paddle *playerPaddle;
    Paddle *computerPaddle;
    Ball *ball;
    QTimer *gameTimer;

    int playerScore;
    int computerScore;
    QGraphicsTextItem *playerScoreText;
    QGraphicsTextItem *computerScoreText;

    void setupScene();
    void startGame();
    void updateScore();
    void resetGame();

// Reinforment Learning:
#ifdef TRAIN_GAME
    int epoch;
    ReinforcementLearning *rl; // Reinforcement Learning objesi
#endif

private slots:
    void gameLoop();

};
#endif // GAME_H
