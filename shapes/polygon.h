#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape
{
public:
    unsigned count;
    Polygon(unsigned cnt, Point3 *verts[], SDL_FColor col, float bias);
};

Polygon::Polygon(unsigned cnt, Point3 *verts[], SDL_FColor col, float bias = 0) : Shape(col), count(cnt)
{
    for (int i = 2; i < count; i++)
        triangles.push_back(new Triangle(verts[0], verts[i - 1], verts[i], colour, bias));
}

#endif
