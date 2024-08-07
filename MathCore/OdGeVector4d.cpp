#include "pch.h"
#include "OdGeVector4d.h"
#include <cmath>

namespace Geometry
{
    OdGeVector4d::OdGeVector4d() : x(0), y(0), z(0), w(0) {}

    OdGeVector4d::OdGeVector4d(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    OdGeVector4d::~OdGeVector4d() {}

    float OdGeVector4d::Length() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    OdGeVector4d OdGeVector4d::Normalize() const
    {
        float length = Length();
        return OdGeVector4d(x / length, y / length, z / length, w / length);
    }

    float OdGeVector4d::DotProduct(const OdGeVector4d& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    void OdGeVector4d::operator+=(const OdGeVector4d& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }

    void OdGeVector4d::operator-=(const OdGeVector4d& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }

    OdGeVector4d OdGeVector4d::operator+(const OdGeVector4d& other) const
    {
        return OdGeVector4d(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    OdGeVector4d OdGeVector4d::operator-(const OdGeVector4d& other) const
    {
        return OdGeVector4d(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    OdGeVector4d OdGeVector4d::operator*(float scalar) const
    {
        return OdGeVector4d(x * scalar, y * scalar, z * scalar, w * scalar);
    }
}
