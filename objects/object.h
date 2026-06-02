#ifndef OBJECT_H
#define OBJECT_H

#include "../_config.h"
#include "../engine/vector3.h"
#include "../primitives/all.h"

class Object
{
public:
    std::vector<Primitive *> primitives;
    ~Object();
    void triangle_vertex_split(std::vector<Triangle *> &, std::vector<Vector3 *> &);
};

#endif
