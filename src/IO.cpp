#include "IO.h"
#include <array>

IO::IO() {}

static void mapColor(enum color c, Uint8& r, Uint8& g, Uint8& b, Uint8& a) {
    a = 255;
    switch (c) {
        case BLACK:   r = 0;   g = 0;   b = 0;   break;
        case RED:     r = 220; g = 20;  b = 60;  break;
        case GREEN:   r = 60;  g = 179; b = 113; break;
        case BLUE:    r = 65;  g = 105; b = 225; break;
        case CYAN:    r = 0;   g = 180; b = 180; break;
        case MAGENTA: r = 186; g = 85;  b = 211; break;
        case YELLOW:  r = 255; g = 215; b = 0;   break;
        case WHITE:   r = 245; g = 245; b = 245; break;
        case ORANGE:  r = 255; g = 140; b = 0;   break;
        case PURPLE:  r = 128; g = 0;   b = 128; break;
        default:      r = 255; g = 255; b = 255; break;
    }
}

int IO::initGraph() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return -1;
    }
    
    if (TTF_Init() != 0) {
        return -1;
    }

    window_ = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width_,
        height_,
        SDL_WINDOW_SHOWN
    );
    if (!window_) {
        return -1;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        return -1;
    }
    
    // Load a default font - try multiple paths for cross-platform compatibility
    const char* fontPaths[] = {
        #ifdef _WIN32
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/consola.ttf",
        #else
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        #endif
    };
    
    for (const char* path : fontPaths) {
        font_ = TTF_OpenFont(path, 24);
        if (font_) break;
    }
    
    if (!font_) {
        // If no system font found, continue without text (won't crash)
        // You could also return -1 here if text is essential
    }

    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    return 0;
}

void IO::clearScreen() {
    if (!renderer_) return;
    Uint8 r, g, b, a;
    mapColor(BLACK, r, g, b, a);
    SDL_SetRenderDrawColor(renderer_, r, g, b, a);
    SDL_RenderClear(renderer_);
}

void IO::updateScreen() {
    if (!renderer_) return;
    SDL_RenderPresent(renderer_);
}

int IO::getScreenHeight() {
    return height_;
}

int IO::getScreenWidth() {
    return width_;
}

void IO::drawText(const std::string& text, int x, int y, enum color pC) {
    if (!renderer_ || !font_) return;
    
    Uint8 r, g, b, a;
    mapColor(pC, r, g, b, a);
    SDL_Color textColor = {r, g, b, a};
    
    SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), textColor);
    if (!surface) return;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer_, texture, nullptr, &destRect);
    
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void IO::drawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC) {
    if (!renderer_) return;

    if (pX2 < pX1) std::swap(pX1, pX2);
    if (pY2 < pY1) std::swap(pY1, pY2);

    SDL_Rect rect{ pX1, pY1, (pX2 - pX1 + 1), (pY2 - pY1 + 1) };
    Uint8 r, g, b, a;
    mapColor(pC, r, g, b, a);
    SDL_SetRenderDrawColor(renderer_, r, g, b, a);
    SDL_RenderFillRect(renderer_, &rect);
}

int IO::pollKey() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return SDLK_ESCAPE;
        }
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.scancode) {
                case SDL_SCANCODE_RIGHT:
                    return SDL_SCANCODE_RIGHT;
                case SDL_SCANCODE_LEFT:
                    return SDL_SCANCODE_LEFT;
                case SDL_SCANCODE_DOWN:
                    return SDL_SCANCODE_DOWN;
                case SDL_SCANCODE_X:
                    return SDL_SCANCODE_X;
                case SDL_SCANCODE_Z:
                    return SDL_SCANCODE_Z;
                case SDL_SCANCODE_R:
                    return SDL_SCANCODE_R;
                case SDL_SCANCODE_ESCAPE:
                    return SDL_SCANCODE_ESCAPE; 
                default:
                    break;
            }
        }
    }
    return 0;
}

int IO::getKey() {
    return 0;  // Not used in current implementation
}

int IO::isKeyDown(int pKey) {
    // Expect pKey to be an SDL_Scancode (e.g., SDL_SCANCODE_LEFT)
    int num = 0;
    const Uint8* state = SDL_GetKeyboardState(&num);
    if (!state) return 0;
    if (pKey < 0 || pKey >= num) return 0;
    return state[pKey] ? 1 : 0;
}
