#ifndef REALITY_H
#define REALITY_H

#include "_config.h"
#include "objects/all.h"
#include "primitives/all.h"
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

void Reality::handle_input(float delta)
{
    SDL_Event event;
    // 1. Handle "Instant" Actions (Events)
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            running = false;
        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.scancode == SDL_SCANCODE_ESCAPE)
                running = false;
            if (DEBUG)
            {
                if (event.key.scancode == SDL_SCANCODE_SPACE)
                    active = !active;
                if (event.key.scancode == SDL_SCANCODE_PRINTSCREEN)
                    debug = true;
            }
        }
        /*
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                std::println("mouse x:{} y:{}", event.button.x, event.button.y);
            }
        }
        */
    }
    const bool *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
        move = move_w * delta;
        move.rotate_about_z(angle);
        pos.translate(move);
    }
    if (state[SDL_SCANCODE_S])
    {
        move = move_w * delta;
        move.rotate_about_z(angle);
        pos.translate_r(move);
    }
    if (state[SDL_SCANCODE_A])
        angle += M_PIf * delta;
    if (state[SDL_SCANCODE_D])
        angle -= M_PIf * delta;
    if (state[SDL_SCANCODE_E])
    {
        move = move_e * delta;
        move.rotate_about_z(angle);
        pos.translate(move);
    }
    if (state[SDL_SCANCODE_Q])
    {
        move = move_e * delta;
        move.rotate_about_z(angle);
        pos.translate_r(move);
    }
    if (DEBUG)
    {
        if (state[SDL_SCANCODE_PAGEUP])
        {
            move = move_u * delta;
            pos.translate(move);
        }
        if (state[SDL_SCANCODE_PAGEDOWN])
        {
            move = move_u * delta;
            pos.translate_r(move);
        }
    }
}

void Reality::loop()
{
    running = active = true;
    float dt = 1.0 / 60;
    while (running)
    {
        auto t0 = microsecs();
        handle_input(dt);
        screen.clear();
        // if (active)
        // physics(dt);
        render();
        screen.update();
        debug = false;
        dt = (microsecs() - t0) / 1000000.0;
    }
}

void Reality::render()
{
    if (debug)
        world.print();
    if (!active)
        return;

    for (auto vertex : world.vertices)
    {
        vertex->calc_cam_rel(pos, angle);
        if (vertex->cam_rel_y > 0)
            vertex->project_2d();
    }

    visible_tris.reserve(world.triangles.size());
    // Step 0 - Calc all triangle distances
    for (auto tri : world.triangles)
        tri->calc_distance();

    // Step 1 - Generate list of visible triangles
    int vis_count = 0;
    for (auto tri : world.triangles)
    {
        // If nothing is in field of vision, then move on... TODO :- EXCEPT WHEN IT OBLITERATES THE SCREEN
        if ((tri->vertices[0]->visible) || (tri->vertices[1]->visible) || (tri->vertices[2]->visible))
        {
            float d = tri->distance;
            // TODO - add this is distance order
            if (d > MAX_RENDER_DISTANCE)
                continue;
            bool placed = false;
            for (int j = 0; j < vis_count; j++)
            {
                if (d > visible_tris[j]->distance)
                {
                    visible_tris.insert(visible_tris.begin() + j, tri);
                    placed = true;
                    break;
                }
            }
            if (!placed)
                visible_tris.push_back(tri);
            vis_count++;
        }
    }
    if (visible_tris.size() > MAX_TRIANGLES)
        visible_tris.erase(visible_tris.begin(), visible_tris.begin() + visible_tris.size() - MAX_TRIANGLES);
    if (debug)
        std::println("{} of {} visible triangles", visible_tris.size(), world.triangles.size());

    // Step 2 - Render visible triangles
    for (auto tri : visible_tris)
    {
        // Calc how many verts are in-front of the camera
        int infrontCount = 0;
        for (int i = 0; i < 3; i++)
            if (tri->vertices[i]->cam_rel_y > 0)
                infrontCount++;
        switch (infrontCount)
        {
        case 3:
            screen.draw_triangle(
                tri->vertices[0]->scrn, tri->vertices[1]->scrn,
                tri->vertices[2]->scrn, tri->colour, DEBUG ? COL_DARK : COL_CLEAR);
            break;
        case 2:
            // calc the 2 intersection points
            // plot QUAD
            break;
        case 1:
            for (int i = 0; i < 3; i++)
            {
                if (tri->vertices[i]->cam_rel_y > 0)
                    for (int j = 0; j < 3; j++)
                        if (i != j)
                        {
                            tri->vertices[j]->project_intersect(tri->vertices[i]);
                        }
            }
            if (DEBUG)
                screen.draw_triangle(
                    tri->vertices[0]->scrn, tri->vertices[1]->scrn,
                    tri->vertices[2]->scrn, COL_B, COL_BRIGHT);
            else
                screen.draw_triangle(
                    tri->vertices[0]->scrn, tri->vertices[1]->scrn,
                    tri->vertices[2]->scrn, tri->colour);
            // calc the 2 intersection point
            // plot triangle
            break;
        }
    }
    visible_tris.clear();
}

#endif
