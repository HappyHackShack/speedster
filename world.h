#ifndef WORLD_H
#define WORLD_H

#include "_config.h"
#include "vector3.h"
#include "triangle.h"
#include "objects/all.h"

class World
{
public:
    std::vector<Object *> objects;
    std::vector<Point3 *> vertices;
    std::vector<Triangle *> triangles;
    ~World();
    void load_level(std::string file_name);
    void print();
    void unload_level();
    void triangle_vertex_split();
};

World::~World()
{
    unload_level();
    if (DEBUG)
        std::println("Bye-bye");
}

void World::load_level(std::string file_name)
{
    std::string line;
    std::ifstream ipf(file_name);
    if (!ipf.is_open())
        throw std::runtime_error("Could not open the level file!");

    std::getline(ipf, line);
    std::println("{}", line);
    // std::istringstream words(line);

    if (1)
    {
        while (std::getline(ipf, line))
        {
            Point3 pt;
            char ot;
            int x, y, z;
            unsigned s;
            std::istringstream params(line);
            params >> ot;
            switch (ot)
            {
            case 'H':
                params >> x >> y >> s;
                z = 0; // until we know floor height
                if (DEBUG)
                    std::println("Making HOUSE @ {},{},{} x{}", x, y, z, s);
                pt.set(x, y, z);
                objects.push_back(new House(&pt, s));
                break;
            case 'T':
                params >> x >> y >> s;
                z = 0; // until we know floor height
                if (DEBUG)
                    std::println("Making TREE @ {},{},{} x{}", x, y, z, s);
                pt.set(x, y, z);
                objects.push_back(new Tree(&pt, s));
                break;
            }
        }
    }
}

void World::print()
{
    std::println("The {} vertices are:", vertices.size());
    for (auto v : vertices)
    {
        v->print();
        std::println("");
    }
    std::println("The {} triangles are:", triangles.size());
    for (auto t : triangles)
        t->print();
}

void World::triangle_vertex_split()
{
    for (auto obj : objects)
    {
        obj->triangle_vertex_split(triangles, vertices);
    }
}

void World::unload_level()
{
    for (auto obj : objects)
        delete obj;
}

#endif
