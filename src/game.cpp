#include "game.h"
#include <string>

Game::Game(Board *board, Pieces *pieces, IO *io, int screenHeight) {
    this->board = board;
    this->pieces = pieces;
    this->io = io;
    this->screenHeight = screenHeight;
    initGame();
}

// Generate a random integer between min and max (inclusive)
int Game::getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Initialize game state
void Game::initGame() {
    srand((unsigned int)time(NULL));
    board->initBoard();
    
    score = 0;
    level = 1;
    totalLinesCleared = 0;

    curPiece = getRandom(0,6);
    curRotation = getRandom(0,3);
    posX = (BOARD_WIDTH / 2) + pieces->getXInitPos(curPiece, curRotation);
    posY = pieces->getYInitPos(curPiece, curRotation);

    nextPiece = getRandom(0,6);
    nextRotation = getRandom(0,3);
    nextPosX = BOARD_WIDTH + 5;
    nextPosY = 5;
}

// Create a new current piece from the next piece
void Game::createNewPiece() {
    curPiece = nextPiece;
    curRotation = nextRotation;
    posX = (BOARD_WIDTH / 2) + pieces->getXInitPos(curPiece, curRotation);
    posY = pieces->getYInitPos(curPiece, curRotation);

    nextPiece = getRandom(0,6);
    nextRotation = getRandom(0,3);
}

// Get the color associated with a piece type
color Game::getPieceColor(int piece) {
    switch(piece) {
        case 0: return YELLOW;    // I piece
        case 1: return CYAN;  // Square piece
        case 2: return ORANGE;  // T piece 
        case 3: return GREEN;   // S piece
        case 4: return RED;     // Z piece
        case 5: return BLUE;    // J piece
        case 6: return PURPLE;  // L piece
        default: return WHITE;
    }
}

// Draw a piece at the given board position
void Game::drawPiece(int x, int y, int piece, int rotation) {
    color pColor = getPieceColor(piece);
    int pixelX = board->getXPosInPixels(x);
    int pixelY = board->getYPosInPixels(y);

    for(int i = 0; i < PIECE_BLOCKS; i++) {
        for(int j = 0; j < PIECE_BLOCKS; j++) {
            if(pieces->getBlockType(piece, rotation, j, i) != 0) {
                io->drawRectangle(pixelX + i * BLOCK_SIZE, pixelY + j * BLOCK_SIZE,
                     (pixelX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                      (pixelY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, pColor);
            }
        }
    }
}

// Draw the game board and stored pieces
void Game::drawBoard() {
    int boardEdgeL= BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int boardEdgeR= BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int boardEdgeT= (screenHeight - (BLOCK_SIZE * BOARD_HEIGHT));

    io->drawRectangle(boardEdgeR + 10, boardEdgeT, boardEdgeR + BOARD_LINE_WIDTH, screenHeight - 1, BLUE);
    io->drawRectangle(boardEdgeL, boardEdgeT, boardEdgeL + BOARD_LINE_WIDTH, screenHeight - 1, BLUE);

    int boardStartX = boardEdgeL + BOARD_LINE_WIDTH;
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            if(!board->isFree(i,j)) {
                io->drawRectangle(boardStartX + i * BLOCK_SIZE, boardEdgeT + j * BLOCK_SIZE,
                    (boardStartX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                    (boardEdgeT + j * BLOCK_SIZE) + BLOCK_SIZE - 1, BLUE);
            }
        }
    }
}

// Draw the entire game scene
void Game::drawScene() {
    io->clearScreen();
    drawBoard();
    drawPiece(posX, posY, curPiece, curRotation);
    drawPiece(nextPosX, nextPosY, nextPiece, nextRotation);
    
    // Draw score in top right corner
    std::string scoreText = "Score: " + std::to_string(score);
    io->drawText(scoreText, 450, 20, WHITE);
    
    // Draw level below score
    std::string levelText = "Level: " + std::to_string(level);
    io->drawText(levelText, 450, 50, WHITE);
    
    // Draw lines cleared
    std::string linesText = "Lines: " + std::to_string(totalLinesCleared);
    io->drawText(linesText, 450, 80, WHITE);
}

int Game::getScore() const {
    return score;
}

void Game::addScore(int points) {
    score += points;
}

int Game::getLevel() const {
    return level;
}

int Game::getLinesCleared() const {
    return totalLinesCleared;
}

void Game::addLinesCleared(int lines) {
    totalLinesCleared += lines;
    // Level up every 10 lines
    level = 1 + (totalLinesCleared / 10);
}

int Game::getDropSpeed() const {
    // Start at 700ms, decrease by 50ms per level, minimum 100ms
    int speed = 700 - ((level - 1) * 50);
    if (speed < 100) speed = 100;
    return speed;
}

void Game::drawGameOver() {
    io->clearScreen();
    std::string gameOverText = "GAME OVER";
    io->drawText(gameOverText, 250, screenHeight / 2 - 20, RED);

    std::string instructions = "Press R to Restart or ESC to Exit";
    io->drawText(instructions, 150, screenHeight / 2 + 40, RED);

    std::string scoreText = "Score: " + std::to_string(score);
    io->drawText(scoreText, 250, 20, WHITE);
    
    std::string levelText = "Level: " + std::to_string(level);
    io->drawText(levelText, 250, 50, WHITE);
    
    std::string linesText = "Lines: " + std::to_string(totalLinesCleared);
    io->drawText(linesText, 250, 80, WHITE);
    io->updateScreen();

    io->pollKey();

    while (true) {
        int key = io->pollKey();
        if (key) {
            if (key == SDL_SCANCODE_R) {
                initGame();
                break;
            } else if (key == SDL_SCANCODE_ESCAPE) {
                exit(0);
            }
        }
    }
}