#include "board.h"

Board::Board(Pieces *pieces, int screenHeight) {
    this->pieces = pieces;
    this->screenHeight = screenHeight;
    initBoard();
}

// Initialize the board to be empty
void Board::initBoard() {
    for(int i = 0; i < BOARD_WIDTH; i++)
    for(int k = 0; k < BOARD_HEIGHT; k++)
    board[i][k] = POS_FREE;
}

// Store a piece on the board at the given position
void Board::storePiece(int piece, int rotation, int x, int y) {
    for(int i = x, k = 0; i < x + PIECE_BLOCKS; i++, k++)
    {
        for(int s = y, t = 0; s < y + PIECE_BLOCKS; s++, t++) {
            if(pieces->getBlockType(piece,rotation,t,k) != 0)
            {
                // Only store if within bounds
                if(i >= 0 && i < BOARD_WIDTH && s >= 0 && s < BOARD_HEIGHT) {
                    board[i][s] = POS_FILLED;
                }
            }
        }
    }
}

// Check if the game is over (if any block is filled in the top row)
bool Board::isGameOver() {
    for(int i = 0; i < BOARD_WIDTH; i++) {
        if(board[i][0] == POS_FILLED) {
            return true;
        } 
    }
    return false;
}

// Delete a single line and move everything above it down
void Board::deleteSingleLine(int y) {
    for(int i = y; i > 0; i--) {
        for(int j = 0; j < BOARD_WIDTH; j++) {
            board[j][i] = board[j][i-1];
        }
    }
}


// Delete all full lines on the board and return count
int Board::deleteLines() {
    int linesDeleted = 0;
    
    for(int y = 0; y < BOARD_HEIGHT; y++) {
        int x = 0;

        while(x < BOARD_WIDTH) {
            if(board[x][y] == POS_FREE) {
                break;
            }
            x++;
        }
        
        if(x == BOARD_WIDTH) {
            deleteSingleLine(y);
            linesDeleted++;
        }
    }
    
    return linesDeleted;
}

// Check if a position on the board is free
bool Board::isFree(int x, int y) {
    // Check bounds first
    if(x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return false;
    }
    return (board[x][y] == POS_FREE);
}

// Convert board X position to pixel position
int Board::getXPosInPixels(int pos) {
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH/2))) + BOARD_LINE_WIDTH + (pos * BLOCK_SIZE));
}

// Convert board Y position to pixel position
int Board::getYPosInPixels (int pos)
{
return ((screenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pos * BLOCK_SIZE));
}

// Check if movement of a piece to a given position is possible
bool Board::isMovementPossible(int x, int y, int piece, int rotation) {
    for(int iX = x, i = 0; iX < x + PIECE_BLOCKS; iX++, i++) {
        for(int jY = y, j = 0; jY < y + PIECE_BLOCKS; jY++, j++) {
            // Check if there's a block at this position in the piece
            if(pieces->getBlockType(piece, rotation, j, i) != 0) {
                // Check if this block would be out of bounds
                if(iX < 0 || iX > BOARD_WIDTH - 1 || jY > BOARD_HEIGHT - 1) {
                    return false;
                }
                // Check if this block would collide with stored pieces (only if in bounds and jY >= 0)
                if(jY >= 0 && !isFree(iX, jY)) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Get the block status at a given board position
int Board::getBlockPiece(int x, int y) {
    // Check bounds first
    if(x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return POS_FREE;
    }
    return board[x][y];
}