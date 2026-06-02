#include "plane.h"

Plane::Plane(float x1, float y1, float x2, float y2, float z, float size, SDL_FColor col) : Shape(col)
{
    for (float x = x1; x < x2; x += size)
        for (float y = y1; y < y2; y += size)
        {
            Point3 *p1 = new Point3(x, y, z);
            Point3 *p2 = new Point3(x + size, y, z);
            Point3 *p3 = new Point3(x + size, y + size, z);
            Point3 *p4 = new Point3(x, y + size, z);
            extra_verts.push_back(p1);
            extra_verts.push_back(p2);
            extra_verts.push_back(p3);
            extra_verts.push_back(p4);
            triangles.push_back(new Triangle(p1, p2, p3, colour, size * 3));
            triangles.push_back(new Triangle(p1, p3, p4, colour, size * 3));
        }
}

Plane::Plane(int size_x, int size_y, std::vector<short> &heights, int size, SDL_FColor col) : Shape(col)
{
    for (int x = 0; x < size_x; x += 1)
        for (int y = 0; y < size_y; y += 1)
        {
            float z1 = (float)heights[y * 100 + x] / 10;
            float z2 = (float)heights[y * 100 + x + 1] / 10;
            float z3 = (float)heights[(y + 1) * 100 + x + 1] / 10;
            float z4 = (float)heights[(y + 1) * 100 + x] / 10;
            Point3 *p1 = new Point3(x * size, y * size, z1);
            Point3 *p2 = new Point3((x + 1) * size, y * size, z2);
            Point3 *p3 = new Point3((x + 1) * size, (y + 1) * size, z3);
            Point3 *p4 = new Point3(x * size, (y + 1) * size, z4);
            extra_verts.push_back(p1);
            extra_verts.push_back(p2);
            extra_verts.push_back(p3);
            extra_verts.push_back(p4);
            triangles.push_back(new Triangle(p1, p2, p3, rand_col(), size * 3));
            triangles.push_back(new Triangle(p1, p3, p4, rand_col(), size * 3));
        }
}
