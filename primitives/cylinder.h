#ifndef CYLINDER_H
#define CYLINDER_H

#include "primitive.h"

class Cylinder : public Primitive
{
public:
    Cylinder(Point3 *p1, float height, float radius, unsigned sectors, SDL_FColor col);
};

Cylinder::Cylinder(Point3 *p1, float height, float radius, unsigned sectors, SDL_FColor col)
{
    // make the points
    Point3 *Bpts[sectors];
    Point3 *Tpts[sectors];
    for (int i = 0; i < sectors; i++)
    {
        float a = 2 * M_PIf / sectors * i;
        Bpts[i] = new Point3(p1->x + radius * sinf(a), p1->y + radius * cosf(a), p1->z);
        Tpts[i] = new Point3(p1->x + radius * sinf(a), p1->y + radius * cosf(a), p1->z + height);
        // and store the points
        vertices.push_back(Bpts[i]);
        vertices.push_back(Tpts[i]);
    }
    // make polygons (and add)
    polygons.push_back(new Polygon(sectors, Bpts, col));
    polygons.push_back(new Polygon(sectors, Tpts, col));
    for (int i = 0; i < sectors; i++)
        polygons.push_back(new Polygon(
            4, (Point3 *[]){Bpts[i], Bpts[(i + 1) % sectors], Tpts[(i + 1) % sectors], Tpts[i]}, col));
}

#endif
