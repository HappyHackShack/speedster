#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape
{
public:
    unsigned count;
    Polygon(unsigned cnt, Point3 *verts[], SDL_FColor col, float bias=0);
};

#endif
