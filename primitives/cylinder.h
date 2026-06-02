#ifndef CYLINDER_H
#define CYLINDER_H

#include "primitive.h"

class Cylinder : public Primitive
{
public:
    Cylinder(Point3 *p1, float height, float radius, unsigned sectors, SDL_FColor col, unsigned ignore_flags = 0);
};

#endif
