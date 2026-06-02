#ifndef SCREEN_H
#define SCREEN_H

#include "../_config.h"

#define ESCAPE SDLK_ESCAPE

class GfxScreen
{
public:
    GfxScreen(float w = SCRN_W, float h = SCRN_H);
    ~GfxScreen();
    void clear();
    void draw_line(SDL_FPoint p1, SDL_FPoint p2, SDL_FColor col);
    void draw_quad(SDL_FPoint p1, SDL_FPoint p2,
                   SDL_FPoint p3, SDL_FPoint p4,
                   SDL_FColor fill, SDL_FColor border);
    void draw_triangle(SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3,
                       SDL_FColor fill, SDL_FColor border);
    void update();
    void testing_text();

private:
    float width;
    float height;
    SDL_Window *window;
    SDL_Renderer *canvas;
};

#endif
