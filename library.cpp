#include "library.h"

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
