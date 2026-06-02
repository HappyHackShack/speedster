#ifndef PLANE_H
#define PLANE_H

#include "shape.h"

class Plane : public Shape
{
public:
    unsigned count;
    Plane(float x1, float y1, float x2, float y2, float z, float size, SDL_FColor col);
    Plane(int size_x, int size_y, std::vector<short> &, int size, SDL_FColor col);
};

#endif
