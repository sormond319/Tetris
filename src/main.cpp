#include "game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    IO io;
    
    if (io.initGraph() != 0) {
        return 1;
    }
    
    int screenHeight = io.getScreenHeight();

    Pieces pieces;
    Board board(&pieces, screenHeight);
    Game game(&board, &pieces, &io, screenHeight);
    unsigned long tickTime = SDL_GetTicks();

    while(!io.isKeyDown(SDL_SCANCODE_ESCAPE)) {
        io.clearScreen();
        game.drawScene();
        io.updateScreen();

        int key = io.pollKey();

        switch (key)
        {
        case SDL_SCANCODE_RIGHT:
            if(board.isMovementPossible(game.posX + 1, game.posY, game.curPiece, game.curRotation)) {
                game.posX += 1;
            }
            break;
        case SDL_SCANCODE_LEFT:
            if(board.isMovementPossible(game.posX - 1, game.posY, game.curPiece, game.curRotation)) {
                game.posX -= 1;
            }
            break;
        case SDL_SCANCODE_DOWN:
            if(board.isMovementPossible(game.posX, game.posY + 1, game.curPiece, game.curRotation)) {
                game.posY += 1;
                game.addScore(1);  // Soft drop: 1 point per cell
            }
            break;
        case SDL_SCANCODE_X:
        {
            int dropDistance = 0;
            while (board.isMovementPossible(game.posX, game.posY + 1, game.curPiece, game.curRotation)) {
                game.posY += 1;
                dropDistance++;
            }
            game.addScore(dropDistance * 2);  // Hard drop: 2 points per cell

            board.storePiece(game.curPiece, game.curRotation, game.posX, game.posY);
            int linesCleared = board.deleteLines();
            
            // Update lines cleared counter
            if (linesCleared > 0) {
                game.addLinesCleared(linesCleared);
            }
            
            // Award points for clearing lines
            if (linesCleared == 1) game.addScore(100);
            else if (linesCleared == 2) game.addScore(300);
            else if (linesCleared == 3) game.addScore(500);
            else if (linesCleared == 4) game.addScore(800);

            if (board.isGameOver()) {
                game.drawGameOver();
            } else {
                game.createNewPiece();
            }
            break;
        }
        case SDL_SCANCODE_Z:
        {
            if(board.isMovementPossible(game.posX, game.posY, game.curPiece, (game.curRotation + 1) % 4)) {
                game.curRotation = (game.curRotation + 1) % 4;
            }
            break;
        }
        }

        unsigned long currentTime = SDL_GetTicks();
        int dropSpeed = game.getDropSpeed();  // Get level-based drop speed
        if (currentTime - tickTime > (unsigned long)dropSpeed) {
            if(board.isMovementPossible(game.posX, game.posY + 1, game.curPiece, game.curRotation)) {
                game.posY += 1;
            } else {
                board.storePiece(game.curPiece, game.curRotation, game.posX, game.posY);
                int linesCleared = board.deleteLines();
                
                // Update lines cleared counter
                if (linesCleared > 0) {
                    game.addLinesCleared(linesCleared);
                }
                
                // Award points for clearing lines
                if (linesCleared == 1) game.addScore(100);
                else if (linesCleared == 2) game.addScore(300);
                else if (linesCleared == 3) game.addScore(500);
                else if (linesCleared == 4) game.addScore(800);
                
                if (board.isGameOver()) {
                    game.drawGameOver();
                } else {
                    game.createNewPiece();
                }
            }
            tickTime = SDL_GetTicks();
        }
    }
    
    return 0;
}