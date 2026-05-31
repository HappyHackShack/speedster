#ifndef CUBOID_H
#define CUBOID_H

#include "primitive.h"

class Cuboid : public Primitive
{
public:
    Cuboid(Point3 *p1, Point3 *p2, SDL_FColor col, unsigned ignore_flags);
};

Cuboid::Cuboid(Point3 *p1, Point3 *p2, SDL_FColor col, unsigned ignore_flags = 0)
{
    // make the points
    for (int i = 0; i < 8; i++)
    {
        vertices.push_back(new Point3(
            ((i & 1) == 0) ? p1->x : p2->x,
            ((i & 2) == 0) ? p1->y : p2->y,
            ((i & 4) == 0) ? p1->z : p2->z));
    }

    // make polygons (and add)
    if ((ignore_flags & IGNORE_BTM) == 0)
        polygons.push_back(new Polygon(4, (Point3 *[]){vertices[0], vertices[1], vertices[3], vertices[2]}, col)); // Btm
    polygons.push_back(new Polygon(4, (Point3 *[]){vertices[0], vertices[2], vertices[6], vertices[4]}, col));     // Left
    polygons.push_back(new Polygon(4, (Point3 *[]){vertices[0], vertices[1], vertices[5], vertices[4]}, col));     // Front
    polygons.push_back(new Polygon(4, (Point3 *[]){vertices[1], vertices[3], vertices[7], vertices[5]}, col));     // Right
    polygons.push_back(new Polygon(4, (Point3 *[]){vertices[2], vertices[3], vertices[7], vertices[6]}, col));     // Back
    if ((ignore_flags & IGNORE_TOP) == 0)
        polygons.push_back(new Polygon(4, (Point3 *[]){vertices[4], vertices[5], vertices[7], vertices[6]}, col)); // Top
}

#endif
