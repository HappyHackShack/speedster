#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../_config.h"
#include "../shapes/all.h"
#include "../engine/vector3.h"

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

#endif
