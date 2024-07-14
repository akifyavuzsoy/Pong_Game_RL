#include "game.h"
#include "ui_game.h"
#include <QDebug>

game::game(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::game)
{
    ui->setupUi(this);
    setupScene();
    startGame();
}

game::~game()
{
    delete ui;
}

void game::setupScene()
{

    scene = new QGraphicsScene(0, 0, GRAPHICS_WIDTH, GRAPHICS_HEIGHT);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setFixedSize(GRAPHICS_WIDTH+50, GRAPHICS_HEIGHT+50);
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(0, 0, 0)));

    //qDebug() << "Scene setup completed";

}

void game::startGame()
{
    playerPaddle = new Paddle(SPACE, GRAPHICS_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT, true);
    computerPaddle = new Paddle(GRAPHICS_WIDTH-PADDLE_WIDTH-SPACE, GRAPHICS_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT, false);
    ball = new Ball(GRAPHICS_WIDTH/2, GRAPHICS_HEIGHT/2, BALL_DIAMETER);

    scene->addItem(playerPaddle);
    scene->addItem(computerPaddle);
    scene->addItem(ball);

    //qDebug() << "Player Paddle added at:" << playerPaddle->pos();
    //qDebug() << "Computer Paddle added at:" << computerPaddle->pos();
    //qDebug() << "Ball added at:" << ball->pos();

    playerPaddle->setFlag(QGraphicsItem::ItemIsFocusable);
    playerPaddle->setFocus();

    // Skorları başlat ve ekrana ekle
    playerScore = 0;
    computerScore = 0;
    playerScoreText = new QGraphicsTextItem(QString::number(playerScore));
    playerScoreText->setDefaultTextColor(Qt::white);
    playerScoreText->setFont(QFont("Arial", 24));
    playerScoreText->setPos(50, 10);
    scene->addItem(playerScoreText);

    computerScoreText = new QGraphicsTextItem(QString::number(computerScore));
    computerScoreText->setDefaultTextColor(Qt::white);
    computerScoreText->setFont(QFont("Arial", 24));
    computerScoreText->setPos(700, 10);
    scene->addItem(computerScoreText);

#ifdef TRAIN_GAME
    rl = new ReinforcementLearning(playerPaddle); // Reinforcement Learning objesini oluştur
#endif

    gameTimer = new QTimer(this);
    /*
    connect(gameTimer, &QTimer::timeout, [this]() {
        playerPaddle->moveUp();
        playerPaddle->moveDown();
    });
    */
    connect(gameTimer, &QTimer::timeout, this, &game::gameLoop);
    gameTimer->start(50);

    //qDebug() << "Game timer started";
}

void game::updateScore()
{
    playerScoreText->setPlainText(QString::number(playerScore));
    computerScoreText->setPlainText(QString::number(computerScore));
}

void game::resetGame()
{
    ball->setPos(GRAPHICS_WIDTH/2, GRAPHICS_HEIGHT/2); // Topu yeniden ortala
    playerPaddle->setPos(SPACE, GRAPHICS_HEIGHT/2);
    computerPaddle->setPos(GRAPHICS_WIDTH-PADDLE_WIDTH-SPACE, GRAPHICS_HEIGHT/2);
    ball->setXVelocity(-ball->getXVelocity()); // Topun yönünü değiştir
    ball->setYVelocity(BALL_VELOCITY);
}

void game::gameLoop()
{

#ifdef TEST_GAME
    // Oyuncu paddle'ının hareketini güncelle
    playerPaddle->moveUp();
    playerPaddle->moveDown();

    // Bilgisayar paddle'ının topa doğru hareket etmesini sağla
    if (ball->y() < computerPaddle->y()) {
        computerPaddle->setPos(computerPaddle->x(), computerPaddle->y() - PADDLE_VELOCITY); // Yukarı hareket et
    } else if (ball->y() + ball->rect().height() > computerPaddle->y() + computerPaddle->rect().height()) {
        computerPaddle->setPos(computerPaddle->x(), computerPaddle->y() + PADDLE_VELOCITY); // Aşağı hareket et
    }

    // Topun sahnenin sağ veya sol kenarına çarpmasını kontrol et
    if (ball->x() <= 0) {
        computerScore++;
        updateScore();

        resetGame();

    } else if (ball->x() + ball->rect().width() >= scene->width()) {
        playerScore++;
        updateScore();
        resetGame();
    }
#endif

#ifdef TRAIN_GAME
    // Reinforcement learning ile paddle'ı kontrol et
    rl->update(ball);



    // Bilgisayar paddle'ının topa doğru hareket etmesini sağla
    if (ball->y() < computerPaddle->y()) {
        computerPaddle->setPos(computerPaddle->x(), computerPaddle->y() - PADDLE_VELOCITY); // Yukarı hareket et
    } else if (ball->y() + ball->rect().height() > computerPaddle->y() + computerPaddle->rect().height()) {
        computerPaddle->setPos(computerPaddle->x(), computerPaddle->y() + PADDLE_VELOCITY); // Aşağı hareket et
    }

    // Topun sahnenin sağ veya sol kenarına çarpmasını kontrol et
    if (ball->x() <= 0) {
        computerScore++;
        updateScore();
        rl->penalize(); // Ceza ver
        resetGame();

    } else if (ball->x() + ball->rect().width() >= scene->width()) {
        playerScore++;
        updateScore();
        rl->reward(); // Ödül ver
        resetGame();
    }

    if (epoch >= 100) {
        rl->saveModel("model.txt"); // Modeli kaydet
        gameTimer->stop();
        qDebug() << "Training completed and model saved.";
    }
#endif


}
