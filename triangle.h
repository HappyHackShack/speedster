#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "_config.h"
#include "vector3.h"

class Triangle
{
public:
    SDL_FColor colour;
    Point3 *vertices[3];
    Triangle(Point3 *p0, Point3 *p1, Point3 *p2, SDL_FColor col)
    {
        vertices[0] = p0;
        vertices[1] = p1;
        vertices[2] = p2;
        colour = col;
    }
    void print()
    {
        std::print("Tri ");
        vertices[0]->print();
        vertices[1]->print();
        vertices[2]->print();
        std::println("");
    }
};

#endif