#include "tree.h"

Tree::Tree(Point3 *base, unsigned size)
{
    Point3 mid = {base->x, base->y, base->z + size / 2.0f};
    primitives.push_back(new Cone(&mid, size / 2.0f, size / 2.0f, tree_sections, COL_LEAVES));
    primitives.push_back(new Cylinder(base, size / 2.0f, size / 8.0f, tree_sections, COL_WOOD, IGNORE_BTM|IGNORE_TOP));
}
