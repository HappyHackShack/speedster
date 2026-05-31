#ifndef CONFIG_H
#define CONFIG_H

// dnf install SDL3-devel SDL3_image-devel SDL3_sound-devel SDL3_ttf-devel

// #include <algorithm>
// #include <array>
#include <chrono>
// #include <format>
#include <fstream>
#include <iostream>
#include <math.h>
// #include <memory>
#include <print>
// #include <ranges>
// #include <set>
// #include <span>
#include <string>
#include <sstream>
// #include <utility>
// #include <unistd.h>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#define DEBUG false

/*********************** SCREEN */
#define SCRN_TITLE "Full 3d Speedster Racing"
#define SCRN_W 1280
#define SCRN_H 800
const int SCRN_W_2 = SCRN_W / 2;
const int SCRN_H_2 = SCRN_H / 2;
const int SCRN_W_4 = SCRN_W / 4;
const int SCRN_3H_4 = 3 * SCRN_H / 4;
const int SCRN_H_4 = SCRN_H / 4;
const int MAX_RENDER_DISTANCE = 100;
const int MAX_TRIANGLES = 1000;

const SDL_FColor COL_CLEAR = {0.0, 0.0, 0.0, 0.0};
const SDL_FColor COL_DARK = {0.0, 0.0, 0.0, 1.0};
const SDL_FColor COL_BRIGHT = {1.0, 1.0, 1.0, 1.0};
const SDL_FColor COL_R = {1.0, 0.0, 0.0, 1.0};
const SDL_FColor COL_G = {0.0, 1.0, 0.0, 1.0};
const SDL_FColor COL_B = {0.0, 0.0, 1.0, 1.0};
const SDL_FColor COL_WOOD = {0.65, 0.50, 0.39, 1.0};
const SDL_FColor COL_LEAVES = {0.0, 0.7, 0.0, 1.0};
const SDL_FColor COL_WALL = {1.0, 1.0, 0.85, 1.0};
const SDL_FColor COL_ROOF = {0.65, 0.0, 0.0, 1.0};
// Standard Web Colours
const SDL_FColor COL_SLATE = {112.0 / 256, 128.0 / 256, 144.0 / 256, 1.0};
const SDL_FColor COL_LIGHT_SLATE = {119.0 / 256, 136.0 / 256, 153.0 / 256, 1.0};

/*********************** Mini Map */
#define MINIMAP_SIZE 200
const unsigned MINIMAP_SIZE_2 = MINIMAP_SIZE / 2;
#define MINIMAP_SCALE 4.0f
#define BLOCK_HEIGHT 5.0f
const int FLOOR_TILE_SIZE = 2;

/*********************** ANSI Colours */

#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE "\033[34m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_CYAN "\033[36m"
#define ANSI_WHITE "\033[37m"
#define ANSI_END "\033[0m"

#define ANSI_BOX_TL U"\u250C"
#define ANSI_BOX_TR U"\u2510"
#define ANSI_BOX_BL U"\u2514"
#define ANSI_BOX_BR U"\u2518"
#define ANSI_BOX_H U'\u2500'
#define ANSI_BOX_V U'\u2502'
#define UC_TICK "✅"
#define UC_CROSS "❌"

/*********************** functions */

uint64_t microsecs()
{
    uint64_t ms = std::chrono::duration_cast<std::chrono::microseconds>(
                      std::chrono::high_resolution_clock::now().time_since_epoch())
                      .count();
    return ms;
}

SDL_FColor rand_col()
{
    srandom(microsecs() % 32768);
    float r = random() % 255 / 255.0;
    float g = random() % 255 / 255.0;
    float b = random() % 255 / 255.0;
    return {r, g, b, 1};
}

#endif
