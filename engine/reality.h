#ifndef REALITY_H
#define REALITY_H

#include "../_config.h"
#include "../objects/all.h"
#include "../primitives/all.h"
#include "reality.h"
#include "screen.h"
#include "triangle.h"
#include "vector3.h"
#include "world.h"

class Reality
{
public:
    float gravity;
    Reality(GfxScreen &scrn, World &wrld) : screen(scrn), world(wrld) {};
    void handle_input(float delta);
    void loop();
    void render();

private:
    bool running, active, debug = false;
    GfxScreen &screen;
    World &world;
    std::vector<Triangle *> visible_tris;
    float angle = 0;
    Vector3 pos{0, 0, 2};
    Vector3 move_w{0, 30, 0};
    Vector3 move_e{30, 0, 0};
    Vector3 move_u{0, 0, 10};
    Vector3 move{};
};

#endif
