#ifndef TREE_H
#define TREE_H

#include "../_config.h"
#include "../vector3.h"
#include "object.h"
#include "../primitives/all.h"

const unsigned tree_sections = 8;

class Tree : public Object
{
public:
    Tree(Point3 *base, unsigned size);
};

Tree::Tree(Point3 *base, unsigned size)
{
    Point3 mid = {base->x, base->y, base->z + size / 2.0f};
    primitives.push_back(new Cone(&mid, size / 2.0f, size / 2.0f, tree_sections, COL_LEAVES));
    primitives.push_back(new Cylinder(base, size / 2.0f, size / 8.0f, tree_sections, COL_WOOD));
}

#endif
