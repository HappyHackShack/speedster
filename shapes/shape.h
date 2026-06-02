#ifndef SHAPE_H
#define SHAPE_H

#include "../_config.h"
#include "../library.h"
#include "../engine/triangle.h"
#include "../engine/vector3.h"

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

#endif
