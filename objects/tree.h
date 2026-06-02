#ifndef TREE_H
#define TREE_H

#include "object.h"

const unsigned tree_sections = 8;

class Tree : public Object
{
public:
    Tree(Point3 *base, unsigned size);
};

#endif
