#ifndef IO_H
#define IO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

// Simple color enum used by drawRectangle
enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, ORANGE, PURPLE};

class IO {
public:
    IO();

    // Rendering
    void drawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
    void clearScreen();
    void updateScreen();
    void drawText(const std::string& text, int x, int y, enum color pC);

    // Init and screen info
    int initGraph();               // returns 0 on success, -1 on failure
    int getScreenHeight();
    int getScreenWidth();

    // Input helpers
    int pollKey();                 // returns 1 if there is a pending event, 0 otherwise
    int getKey();                  // returns an SDL_Keycode (int) or -1 if none
    int isKeyDown(int pKey);       // pKey expects SDL_Scancode (e.g., SDL_SCANCODE_LEFT)

private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    TTF_Font* font_ = nullptr;
    int width_ = 640;
    int height_ = 480;

    // Cached last key from polling
    SDL_Keycode lastKey_ = SDLK_UNKNOWN;
};

#endif // IO_H