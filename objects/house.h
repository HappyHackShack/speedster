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

#endif
