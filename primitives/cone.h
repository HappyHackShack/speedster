#ifndef CONE_H
#define CONE_H

#include "primitive.h"

class Cone : public Primitive
{
public:
    Cone(Point3 *p1, float height, float radius, unsigned sectors, SDL_FColor col, unsigned ignore_flags);
};

Cone::Cone(Point3 *p1, float height, float radius, unsigned sectors, SDL_FColor col, unsigned ignore_flags = 0)
{
    // make the points
    Point3 *top = new Point3(p1->x, p1->y, p1->z + height);
    for (int i = 0; i < sectors; i++)
    {
        float a = 2 * M_PIf / sectors * i + M_PIf /sectors;
        vertices.push_back(new Point3(p1->x + radius * sinf(a), p1->y + radius * cosf(a), p1->z));
    }
    // make polygons (and add)
    if ((ignore_flags & IGNORE_BTM) == 0)
        polygons.push_back(new Polygon(sectors, vertices.data(), col));
    for (int i = 0; i < sectors; i++)
        polygons.push_back(new Polygon(3, (Point3 *[]){vertices[i], vertices[(i + 1) % sectors], top}, col));
    vertices.push_back(top);
}

#endif
