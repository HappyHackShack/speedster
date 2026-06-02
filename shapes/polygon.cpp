#include "polygon.h"

Polygon::Polygon(unsigned cnt, Point3 *verts[], SDL_FColor col, float bias) : Shape(col), count(cnt)
{
    for (int i = 2; i < count; i++)
        triangles.push_back(new Triangle(verts[0], verts[i - 1], verts[i], colour, bias));
}
