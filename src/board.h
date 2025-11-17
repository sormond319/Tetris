#ifndef BOARD
#define BOARD

#include "pieces.h"

#define BOARD_LINE_WIDTH 6 // Width of each of the two lines that delimit the board
#define BLOCK_SIZE 16 // Width and Height of each block of a piece
#define BOARD_POSITION 320 // Center position of the board from the left of the screen
#define BOARD_WIDTH 10 // Board width in blocks
#define BOARD_HEIGHT 20 // Board height in blocks
#define MIN_VERTICAL_MARGIN 20 // Minimum vertical margin for the board limit
#define MIN_HORIZONTAL_MARGIN 20 // Minimum horizontal margin for the board limit
#define PIECE_BLOCKS 5 // Number of horizontal and vertical blocks of a matrix piece

class Board {
    public:
    Board(Pieces *pieces, int ScreenHeight);

    int getXPosInPixels(int pos);
    int getYPosInPixels(int pos);
    bool isFree(int x, int y);
    bool isMovementPossible(int x, int y, int piece, int rotation);
    void storePiece(int piece, int rotation, int x, int y);
    int deleteLines();  // Now returns number of lines deleted
    bool isGameOver();
    int getBlockPiece(int x, int y);
    void initBoard();

    private:
    enum {POS_FREE = -1,POS_FILLED};
    int board[BOARD_WIDTH][BOARD_HEIGHT];
    Pieces *pieces;
    int screenHeight;
    void deleteSingleLine(int y);
};

#endif