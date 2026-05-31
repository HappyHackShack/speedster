#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../_config.h"
#include "../shapes/all.h"
#include "../vector3.h"

#define IGNORE_BTM 1
#define IGNORE_TOP 2

class Primitive
{
public:
    ~Primitive();
    std::vector<Shape *> shapes;
    std::vector<Point3 *> vertices;
    void triangle_vertex_split(std::vector<Triangle *> &, std::vector<Vector3 *> &);
};

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

#endif
