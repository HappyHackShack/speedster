#ifndef CUBOID_H
#define CUBOID_H

#include "primitive.h"

class Cuboid : public Primitive
{
public:
    Cuboid(Point3 *p1, Point3 *p2, SDL_FColor col, unsigned ignore_flags = 0);
};

#endif
