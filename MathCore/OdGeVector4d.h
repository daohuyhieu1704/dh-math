#pragma once

namespace Geometry
{
    class OdGeVector4d
    {
    public:
        OdGeVector4d();
        OdGeVector4d(float x, float y, float z, float w);
        ~OdGeVector4d();

        float Length() const;
        OdGeVector4d Normalize() const;
        float DotProduct(const OdGeVector4d& other) const;

        void operator+=(const OdGeVector4d& other);
        void operator-=(const OdGeVector4d& other);
        OdGeVector4d operator+(const OdGeVector4d& other) const;
        OdGeVector4d operator-(const OdGeVector4d& other) const;
        OdGeVector4d operator*(float scalar) const;

        float x;
        float y;
        float z;
        float w;
    };
}
