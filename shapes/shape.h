#ifndef SHAPE_H
#define SHAPE_H

#include "../_config.h"
#include "../vector3.h"
#include "../triangle.h"

class Shape
{
public:
    Shape(SDL_FColor col);
    ~Shape();
    // unsigned texture_id = 0;
    SDL_FColor colour;
    std::vector<Triangle *> triangles;
    std::vector<Point3 *> extra_verts;
    void triangle_vertex_split(std::vector<Triangle *> &,  std::vector<Vector3 *> &);
};

Shape::Shape(SDL_FColor col) : colour(col)
{
}

Shape::~Shape()
{
    for (auto tri : triangles)
        delete tri;
    for (auto vert : extra_verts)
        delete vert;
}

void Shape::triangle_vertex_split(std::vector<Triangle *> &all_triangles, std::vector<Vector3 *> &all_vertices)
{
    for (auto triangle : triangles)
        all_triangles.push_back(triangle);
    for (auto vertex : extra_verts)
        all_vertices.push_back(vertex);
}

#endif
