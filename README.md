# Tetris

A classic Tetris implementation in C++ using SDL2.

![Tetris Game](https://img.shields.io/badge/C%2B%2B-11-blue.svg)
![SDL2](https://img.shields.io/badge/SDL2-2.0-green.svg)

![Image of the game running](tetris.png)

## Features
- **Level progression** - game speed increases every 10 lines cleared
- **Scoring system**:
  - Soft drop: 1 point per cell
  - Hard drop: 2 points per cell
  - Line clears: 100 (single), 300 (double), 500 (triple), 800 (tetris)
- **On-screen HUD** displaying score, level, and lines cleared

## Controls

| Key | Action |
|-----|--------|
| **←** | Move piece left |
| **→** | Move piece right |
| **↓** | Soft drop (faster fall) |
| **Z** | Rotate piece clockwise |
| **X** | Hard drop (instant drop) |
| **ESC** | Quit game |

## Requirements

### Linux
- SDL2 development libraries
- SDL2_ttf development libraries
- g++ compiler with C++11 support
- make

## Project Structure

```
Tetris/
├── src/
│   ├── main.cpp      # Main game loop
│   ├── game.cpp/h    # Game logic and state
│   ├── board.cpp/h   # Game board management
│   ├── pieces.cpp/h  # Tetromino definitions
│   └── IO.cpp/h      # SDL2 rendering and input
├── build/            # Compiled object files
├── Makefile          # Build configuration
└── README.md         # This file
```
# Credits

Tetris tutorial in C++ by Javier Lopez - https://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/
(Basic game functionality is based off of this guide)