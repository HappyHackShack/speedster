#ifndef POLYGON_H
#define POLYGON_H

#include "_config.h"
#include "vector3.h"
#include "triangle.h"

class Polygon
{
public:
    bool visible = true;
    unsigned count;
    unsigned texture_id = 0;
    SDL_FColor colour;
    std::vector<Triangle *> triangles;
    Polygon(unsigned cnt, Point3 *verts[], SDL_FColor col);
    ~Polygon();
    void triangle_split(std::vector<Triangle *> &);
};

Polygon::Polygon(unsigned cnt, Point3 *verts[], SDL_FColor col) : count(cnt), colour(col)
{
    for (int i = 2; i < count; i++)
        triangles.push_back(new Triangle(verts[0], verts[i - 1], verts[i], colour));
}

Polygon::~Polygon()
{
    for (auto triangle : triangles)
        delete triangle;
}

void Polygon::triangle_split(std::vector<Triangle *> &all_triangles)
{
    for (auto triangle : triangles)
        all_triangles.push_back(triangle);
}

#endif
