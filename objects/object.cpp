#include "object.h"

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
