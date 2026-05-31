#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "_config.h"
#include "vector3.h"

class Triangle
{
public:
    SDL_FColor colour;
    Point3 *vertices[3];
    float distance, distance_bias;
    Triangle(Point3 *p0, Point3 *p1, Point3 *p2, SDL_FColor col, float d_bias=0)
    {
        vertices[0] = p0;
        vertices[1] = p1;
        vertices[2] = p2;
        colour = col;
        distance_bias = d_bias;
    }
    float calc_distance()
    {
        Vector3 midpoint;
        midpoint.cam_rel_x = (vertices[0]->cam_rel_x + vertices[1]->cam_rel_x + vertices[2]->cam_rel_x) / 3;
        midpoint.cam_rel_y = (vertices[0]->cam_rel_y + vertices[1]->cam_rel_y + vertices[2]->cam_rel_y) / 3;
        midpoint.cam_rel_z = (vertices[0]->cam_rel_z + vertices[1]->cam_rel_z + vertices[2]->cam_rel_z) / 3;
        distance = midpoint.distance() + distance_bias;
        return distance;
    }
    void print()
    {
        std::print("Tri ");
        vertices[0]->print();
        vertices[1]->print();
        vertices[2]->print();
        std::println("");
    }
};

#endif