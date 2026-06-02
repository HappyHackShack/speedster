#ifndef CONE_H
#define CONE_H

#include "primitive.h"

class Cone : public Primitive
{
public:
    Cone(Point3 *p1, float height, float radius, unsigned sectors, SDL_FColor col, unsigned ignore_flags = 0);
};

#endif
