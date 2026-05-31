#ifndef SCREEN_H
#define SCREEN_H

#include "_config.h"

#define ESCAPE SDLK_ESCAPE

class GfxScreen
{
public:
    GfxScreen(float w, float h);
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

GfxScreen::GfxScreen(float w = SCRN_W, float h = SCRN_H) : width(w), height(h)
{
    // SDL3 uses bool returns for success/failure
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Init failed: %s", SDL_GetError());
        exit(1);
    }
    TTF_Init();

    // New combined function to create both window and renderer
    if (!SDL_CreateWindowAndRenderer("speedsters", width, height, 0, &window, &canvas))
    {
        SDL_Log("Window/Renderer failed: %s", SDL_GetError());
        exit(1);
    }
    // SDL_SetWindowFullscreen(window, true);
    SDL_SetRenderVSync(canvas, 0);
}

GfxScreen::~GfxScreen()
{
    TTF_Quit();
    SDL_DestroyRenderer(canvas);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GfxScreen::clear()
{
    SDL_RenderClear(canvas);
    SDL_FRect whole_scrn = {0, 0, SCRN_W, SCRN_H};
    SDL_SetRenderDrawColorFloat(canvas, 0, 0, 0, 1);
    SDL_RenderFillRect(canvas, &whole_scrn);
}

void GfxScreen::draw_line(SDL_FPoint p1, SDL_FPoint p2, SDL_FColor col)
{
    SDL_SetRenderDrawColorFloat(canvas, col.r, col.g, col.b, col.a);
    SDL_RenderLine(canvas, p1.x, p1.y, p2.x, p2.y);
}

void GfxScreen::draw_quad(SDL_FPoint p1, SDL_FPoint p2, SDL_FPoint p3, SDL_FPoint p4,
                          SDL_FColor fill, SDL_FColor border)
{
    // Render the filled quadrilateral
    if (fill.a != 0)
    {
        SDL_Vertex vertices[4];
        vertices[0] = {p1, fill, {0, 0}}; // the last 0,0 are the texture coords (for later)
        vertices[1] = {p2, fill, {0, 0}};
        vertices[2] = {p3, fill, {0, 0}};
        vertices[3] = {p4, fill, {0, 0}};
        int indices[6] = {0, 1, 2, 2, 3, 0};
        SDL_RenderGeometry(canvas, NULL, vertices, 4, indices, 6);
    }
    // Render the border
    if (border.a != 0)
    {
        SDL_FPoint points[] = {p1, p2, p3, p4, p1};
        SDL_SetRenderDrawColorFloat(canvas, border.r, border.g, border.b, border.a);
        SDL_RenderLines(canvas, points, 5);
    }
}

void GfxScreen::draw_triangle(SDL_FPoint p1, SDL_FPoint p2,
                              SDL_FPoint p3, SDL_FColor fill, SDL_FColor border = COL_CLEAR)
{
    // Render the filled triangle
    if (fill.a != 0)
    {
        SDL_Vertex vertices[3];
        vertices[0] = {p1, fill, {0, 0}}; // the last 0,0 are the texture coords (for later)
        vertices[1] = {p2, fill, {0, 0}};
        vertices[2] = {p3, fill, {0, 0}};
        SDL_RenderGeometry(canvas, NULL, vertices, 3, NULL, 0);
    }
    // Render the border
    if (border.a != 0)
    {
        SDL_FPoint points[] = {p1, p2, p3, p1};
        SDL_SetRenderDrawColorFloat(canvas, border.r, border.g, border.b, border.a);
        SDL_RenderLines(canvas, points, 4);
    }
}

void GfxScreen::update()
{
    SDL_SetRenderTarget(canvas, NULL);
    SDL_RenderPresent(canvas);
}

void GfxScreen::testing_text()
{
    TTF_Font *font = TTF_OpenFont("fonts/control-freak.ttf" /*path*/, 32 /*size*/);
    SDL_Color color = {200, 225, 255, 255};
    SDL_Surface *surf = TTF_RenderText_Blended(font, "Hello World", 0, color);
    SDL_Texture *text = SDL_CreateTextureFromSurface(canvas, surf);
    SDL_FRect bound{25, 400, 200, 50};
    SDL_RenderTexture(canvas, text, nullptr, &bound);
    SDL_DestroySurface(surf);
    SDL_DestroyTexture(text);
    TTF_CloseFont(font);
}

#endif
