#ifndef OBJECT_H
#define OBJECT_H

#include "../_config.h"
#include "../vector3.h"
#include "../primitives/all.h"

class Object
{
public:
    std::vector<Primitive *> primitives;
    ~Object();
    void triangle_vertex_split(std::vector<Triangle *> &, std::vector<Vector3 *> &);
};

Object::~Object()
{
    for (auto prim : primitives)
        delete prim;
}

void Object::triangle_vertex_split(std::vector<Triangle *> &triangles, std::vector<Vector3 *> &vertices)
{
    for (auto prim : primitives)
    {
        prim->triangle_vertex_split(triangles, vertices);
    }
}

#endif
