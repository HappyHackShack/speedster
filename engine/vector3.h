#ifndef VECTOR3_H
#define VECTOR3_H

#include "../_config.h"

// For an FoV of 90d, Focal len should = SCRN_W_2
const float FOCAL_LEN = SCRN_W_2; // "Zoom" level
const float Near_y = 0.1;

class Vector3
{
public:
    float x, y, z;
    float cam_rel_x, cam_rel_y, cam_rel_z;
    SDL_FPoint scrn;
    bool visible;

    Vector3() : x(0), y(0), z(0) {};
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
    Vector3 &operator=(const Vector3 &v2);
    Vector3 operator*(float s);
    Vector3 operator/(float s);
    Vector3 operator+(const Vector3 &v2);
    Vector3 operator-(const Vector3 &v2);

    float get_rel_x() const { return cam_rel_x; }
    float get_rel_y() const { return cam_rel_y; }
    float get_rel_z() const { return cam_rel_z; }
    void calc_cam_rel(Vector3 &pos, float rot);
    Vector3 cross_prod(Vector3 &v2) const;
    float dot_prod(Vector3 &v2) const;
    float len(Vector3 &v2) const;
    float distance() const;
    void print() const;
    void print_cam() const;
    void print_scrn() const;
    void project_2d();
    void project_intersect(Vector3 *src);
    void rotate_about_z(float a);
    void set(float X, float Y, float Z);
    void translate(Vector3 &v2);
    void translate_r(Vector3 &v2);

private:
};

using Point3 = Vector3;

#endif
