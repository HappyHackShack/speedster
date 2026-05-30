#ifndef VECTOR3_H
#define VECTOR3_H

// Hello World

#include "_config.h"

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
    float len() const;
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

Vector3 &Vector3::operator=(const Vector3 &v2)
{
    if (this == &v2)
        return *this;
    x = v2.x;
    y = v2.y;
    z = v2.z;
    return *this;
}

Vector3 Vector3::operator*(float s)
{
    return Vector3{x * s, y * s, z * s};
}

Vector3 Vector3::operator/(float s)
{
    return Vector3{x / s, y / s, z / s};
}

Vector3 Vector3::operator+(const Vector3 &v2)
{
    return Vector3{x + v2.x, y + v2.y, z + v2.z};
}

Vector3 Vector3::operator-(const Vector3 &v2)
{
    return Vector3{x - v2.x, y - v2.y, z - v2.z};
}

void Vector3::calc_cam_rel(Vector3 &pos, float rot)
{
    // This isn't the fastest method - but will be called many, many times :(
    Vector3 v = *this;
    v.translate_r(pos);
    v.rotate_about_z(-rot);
    cam_rel_x = v.x;
    cam_rel_y = v.y;
    cam_rel_z = v.z;
    visible = ((cam_rel_y > abs(cam_rel_x)) && (cam_rel_y > abs(cam_rel_z)));
}

Vector3 Vector3::cross_prod(Vector3 &v2) const
{
    // Needs testing added
    return Vector3{
        y * v2.z - z * v2.y,
        z * v2.x - x * v2.z,
        x * v2.y - y * v2.x};
}

float Vector3::dot_prod(Vector3 &v2) const
{
    return (x * v2.x + y * v2.y + z * v2.z);
}

float Vector3::len() const
{
    return sqrt(x * x + y * y + z * z);
}

void Vector3::print() const
{
    std::print("({:.2f},{:.2f},{:.2f})", x, y, z);
}

void Vector3::print_cam() const
{
    std::print("({:.2f},{:.2f},{:.2f})", cam_rel_x, cam_rel_y, cam_rel_z);
}

void Vector3::print_scrn() const
{
    std::print("({:.0f},{:.0f})", scrn.x, scrn.y);
}

void Vector3::project_2d()
{
    if (cam_rel_y > 0)
    {
        scrn = {SCRN_W_2 + cam_rel_x * FOCAL_LEN / cam_rel_y,
                SCRN_H_2 - cam_rel_z * FOCAL_LEN / cam_rel_y};
    }
}

void Vector3::project_intersect(Vector3 *src)
{
    Vector3 dif = Vector3{cam_rel_x - src->cam_rel_x, cam_rel_y - src->cam_rel_y, cam_rel_z - src->cam_rel_z};
    float s = (Near_y - src->cam_rel_y) / (dif.y);
    float tmp_x = cam_rel_x - s * dif.x;
    float tmp_z = cam_rel_z - s * dif.z;
    scrn = {SCRN_W_2 + (tmp_x * FOCAL_LEN) / Near_y,
            SCRN_H_2 - (tmp_z * FOCAL_LEN) / Near_y};
}

void Vector3::rotate_about_z(float a)
{
    float x1 = x * cosf(a) - y * sinf(a);
    float y1 = x * sinf(a) + y * cosf(a);
    x = x1;
    y = y1;
}

void Vector3::set(float X, float Y, float Z)
{
    x = X;
    y = Y;
    z = Z;
}

void Vector3::translate(Vector3 &v2)
{
    x += v2.x;
    y += v2.y;
    z += v2.z;
}

void Vector3::translate_r(Vector3 &v2)
{
    x -= v2.x;
    y -= v2.y;
    z -= v2.z;
}

using Point3 = Vector3;

#endif
