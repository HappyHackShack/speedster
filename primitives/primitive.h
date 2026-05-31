#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../_config.h"
#include "../polygon.h"
#include "../vector3.h"

#define IGNORE_BTM 1
#define IGNORE_TOP 2

class Primitive
{
public:
    ~Primitive();
    std::vector<Polygon *> polygons;
    std::vector<Point3 *> vertices;
    void triangle_vertex_split(std::vector<Triangle *> &, std::vector<Vector3 *> &);
};

Primitive::~Primitive()
{
    for (auto poly : polygons)
        delete poly;
    for (auto point : vertices)
        delete point;
}

void Primitive::triangle_vertex_split(std::vector<Triangle *> &triangles, std::vector<Vector3 *> &all_vertices)
{
    for (auto poly : polygons)
    {
        poly->triangle_split(triangles);
    }
    for (auto vertex : vertices)
        all_vertices.push_back(vertex);
}

#endif
