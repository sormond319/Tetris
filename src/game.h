#ifndef GAME
#define GAME

#include "board.h"
#include "pieces.h"
#include "IO.h"
#include <time.h>

#define WAIT_TIME 700

class Game {
    public:
    Game(Board *board, Pieces *pieces, IO *io, int screenHeight);
    void drawScene();
    void createNewPiece();
    color getPieceColor(int piece);
    int getScore() const;
    void addScore(int points);
    int getLevel() const;
    int getLinesCleared() const;
    void addLinesCleared(int lines);
    int getDropSpeed() const;  // Returns milliseconds between drops based on level
    void drawGameOver();

    int posX, posY;
    int curPiece, curRotation;

    private:
    int screenHeight;
    int nextPosX, nextPosY;
    int nextPiece, nextRotation;
    int score;
    int level;
    int totalLinesCleared;

    Board *board;
    Pieces *pieces;
    IO *io;

    int getRandom(int min, int max);
    void initGame();
    void drawPiece(int x, int y, int piece, int rotation);
    void drawBoard();
};
#endif