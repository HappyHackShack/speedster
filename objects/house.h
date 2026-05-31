#ifndef HOUSE_H
#define HOUSE_H

#include "object.h"

class House : public Object
{
public:
    House(Point3 *base, unsigned size);

private:
    const unsigned roof_sides = 4;
};

House::House(Point3 *base, unsigned size)
{
    Point3 p1 = {base->x - size/2, base->y - size/2, base->z};
    Point3 p2 = {base->x + size/2, base->y + size/2, base->z + size/2};
    Point3 mid = {base->x, base->y, base->z + size/2};
    primitives.push_back(new Cone(&mid, size/2, size/2*M_SQRT2f, roof_sides, COL_ROOF, IGNORE_BTM));
    primitives.push_back(new Cuboid(&p1, &p2, COL_WALL, IGNORE_BTM|IGNORE_TOP));
}

#endif
