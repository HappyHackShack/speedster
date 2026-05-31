#ifndef PLANE_H
#define PLANE_H

#include "shape.h"

class Plane : public Shape
{
public:
    unsigned count;
    Plane(float x1, float y1, float x2, float y2, float size, float z, SDL_FColor col);
};

Plane::Plane(float x1, float y1, float x2, float y2, float size, float z, SDL_FColor col) : Shape(col)
{
    for (float x = x1; x < x2; x += size)
        for (float y = y1; y < y2; y += size)
        {
            Point3 *p1 = new Point3(x, y, z);
            Point3 *p2 = new Point3(x + size, y, z);
            Point3 *p3 = new Point3(x + size, y + size, z);
            Point3 *p4 = new Point3(x, y + size, z);
            extra_verts.push_back(p1);
            extra_verts.push_back(p2);
            extra_verts.push_back(p3);
            extra_verts.push_back(p4);
            triangles.push_back(new Triangle(p1, p2, p3, colour, size * 3));
            triangles.push_back(new Triangle(p1, p3, p4, colour, size * 3));
        }
}

#endif
