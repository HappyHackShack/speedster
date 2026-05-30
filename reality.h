#ifndef REALITY_H
#define REALITY_H

#include "_config.h"
#include "vector3.h"
#include "screen.h"
#include "triangle.h"
#include "primitives/all.h"
#include "objects/all.h"
#include "reality.h"
#include "world.h"

class Reality
{
public:
    float gravity;
    Reality(GfxScreen &scrn, World &wrld) : screen(scrn), world(wrld) {};
    void handle_input();
    void loop();
    void render();

private:
    bool running, active, debug = false;
    GfxScreen &screen;
    World &world;
    float angle = 0;
    Vector3 pos{0, 0, 2};
    Vector3 move_w{0, .5, 0};
    Vector3 move_e{0.5, 0, 0};
    Vector3 move{};
};

void Reality::handle_input()
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
            if (event.key.scancode == SDL_SCANCODE_SPACE)
                active = !active;
            if (event.key.scancode == SDL_SCANCODE_LSHIFT)
                debug = true;
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
        move = move_w;
        move.rotate_about_z(angle);
        pos.translate(move);
    }
    if (state[SDL_SCANCODE_S])
    {
        move = move_w;
        move.rotate_about_z(angle);
        pos.translate_r(move);
    }
    if (state[SDL_SCANCODE_A])
        angle += M_PIf / 60;
    if (state[SDL_SCANCODE_D])
        angle -= M_PIf / 60;
    if (state[SDL_SCANCODE_E])
    {
        move = move_e;
        move.rotate_about_z(angle);
        pos.translate(move);
    }
    if (state[SDL_SCANCODE_Q])
    {
        move = move_e;
        move.rotate_about_z(angle);
        pos.translate_r(move);
    }
}

void Reality::loop()
{
    running = active = true;
    float dt = 1.0 / 60;
    while (running)
    {
        auto t0 = microsecs();
        handle_input();
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

    Vector3 cam{0, 0, 10};
    for (auto vertex : world.vertices)
    {
        vertex->calc_cam_rel(pos, angle);
        if (vertex->cam_rel_y > 0)
            vertex->project_2d();
    }
    for (auto tri : world.triangles)
    {
        // If nothing is in field of vision, then move on... TODO :- EXCEPT WHEN IT OBLITERATES THE SCREEN
        if ((!tri->vertices[0]->visible) && (!tri->vertices[1]->visible) && (!tri->vertices[2]->visible))
            continue;
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
                tri->vertices[2]->scrn, tri->colour, COL_DARK);
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
            screen.draw_triangle(
                tri->vertices[0]->scrn, tri->vertices[1]->scrn,
                tri->vertices[2]->scrn, COL_B, COL_BRIGHT);
            // calc the 2 intersection point
            // plot triangle
            break;
        }
    }
    /*
    SDL_FPoint t1{125, 25}, t2{200, 75}, t3{125, 125};
    screen.draw_triangle(t1, t2, t3, COL_CLEAR, COL_WOOD);
    t1.x += 100;
    t2.x += 100;
    t3.x += 100;
    screen.draw_triangle(t1, t2, t3, COL_LEAVES, COL_CLEAR);
    t1.x += 100;
    t2.x += 100;
    t3.x += 100;
    screen.draw_triangle(t1, t2, t3, COL_WALL, COL_LEAVES);

    // Basic Quadrilaterals
    SDL_FPoint q1{125, 200}, q2{200, 225}, q3{200, 275}, q4{125, 325};
    screen.draw_quad(q1, q2, q3, q4, COL_CLEAR, COL_LEAVES);
    q1.x += 100;
    q2.x += 100;
    q3.x += 100;
    q4.x += 100;
    screen.draw_quad(q1, q2, q3, q4, COL_LEAVES, COL_CLEAR);
    q1.x += 100;
    q2.x += 100;
    q3.x += 100;
    q4.x += 100;
    screen.draw_quad(q1, q2, q3, q4, COL_SLATE, COL_ROOF);
    */
    /*
    for (int i = 0; i < world.triangles.size(); i++)
    world.triangles[i]->render(screen);
    */
}

#endif
