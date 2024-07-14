#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game *pongGame = new game();
    pongGame->show();

    return a.exec();
}
