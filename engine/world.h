#ifndef WORLD_H
#define WORLD_H

#include "../_config.h"
#include "../objects/all.h"
#include "../shapes/all.h"
#include "vector3.h"
#include "triangle.h"

#define MAP_SIZE 100

class World
{
public:
    std::vector<Object *> objects;
    std::vector<Shape *> shapes;
    std::vector<Point3 *> vertices;
    std::vector<Triangle *> triangles;
    std::vector<short> height_map;
    ~World();
    void load_level(std::string file_name);
    void print();
    void unload_level();
    void triangle_vertex_split();
};

#endif
