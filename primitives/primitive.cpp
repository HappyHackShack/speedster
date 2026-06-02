#include "primitive.h"

Primitive::~Primitive()
{
    for (auto shape : shapes)
        delete shape;
    for (auto point : vertices)
        delete point;
}

void Primitive::triangle_vertex_split(std::vector<Triangle *> &all_triangles, std::vector<Vector3 *> &all_vertices)
{
    for (auto shape : shapes)
        shape->triangle_vertex_split(all_triangles, all_vertices);
    for (auto vertex : vertices)
        all_vertices.push_back(vertex);
}
