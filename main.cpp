// main.cpp - 程序入口
#include <QApplication>
#include "SudokuGame.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    SudokuGame game;
    game.show();

    return app.exec();
}
