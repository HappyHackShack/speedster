#include "world.h"

World::~World()
{
    unload_level();
    if (DEBUG)
        std::println("Bye-bye");
}

void World::load_level(std::string file_name)
{
    std::string line;
    std::ifstream ipf("levels" + file_name);
    if (!ipf.is_open())
        throw std::runtime_error("Could not open the level file!");

    std::getline(ipf, line);
    std::println("{}", line);

    height_map.assign((MAP_SIZE + 1) * (MAP_SIZE + 1), 0);
    height_map[MAP_SIZE * 5 + 10] = 10;
    height_map[MAP_SIZE * 10 + 20] = 15;
    height_map[MAP_SIZE * 15 + 30] = 20;
    for (int y = 10; y < 20; y++)
        for (int x = 10; x < 20; x++)
            height_map[MAP_SIZE * (y) + x] = 20 * (10 - (abs(15 - x) + abs(15 - y)));
    if (DEBUG)
        std::println("Test values set");

    shapes.push_back(new Plane(MAP_SIZE, MAP_SIZE, height_map, 2, COL_LIGHT_SLATE));
    // shapes.push_back(new Plane(-50,-50,50,50,2,10,COL_LIGHT_SLATE));

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
    for (auto sh : shapes)
        sh->triangle_vertex_split(triangles, vertices);
    for (auto obj : objects)
        obj->triangle_vertex_split(triangles, vertices);
}

void World::unload_level()
{
    for (auto obj : objects)
        delete obj;
}
