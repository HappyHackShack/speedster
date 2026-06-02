#include "cylinder.h"

Cylinder::Cylinder(Point3 *p1, float height, float radius, unsigned sectors, SDL_FColor col, unsigned ignore_flags)
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
    if ((ignore_flags & IGNORE_BTM) == 0)
        shapes.push_back(new Polygon(sectors, Bpts, col));
    if ((ignore_flags & IGNORE_TOP) == 0)
        shapes.push_back(new Polygon(sectors, Tpts, col));
    for (int i = 0; i < sectors; i++)
        shapes.push_back(new Polygon(
            4, (Point3 *[]){Bpts[i], Bpts[(i + 1) % sectors], Tpts[(i + 1) % sectors], Tpts[i]}, col));
}
