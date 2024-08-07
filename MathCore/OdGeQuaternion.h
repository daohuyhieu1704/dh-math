////#pragma once
////#include "OdGeVector3d.h"
////#include "OdGeVector2d.h"
////#include <cmath>
////#include <iostream>
////#include "Matrices.h"
////
////namespace Geometry
////{
////    struct Quaternion
////    {
////        float s;    // scalar part, s
////        float x;    // vector part (x, y, z)
////        float y;
////        float z;
////
////        // ctors
////        Quaternion() : s(0), x(0), y(0), z(0) {}
////        Quaternion(float s, float x, float y, float z) : s(s), x(x), y(y), z(z) {}
////        Quaternion(const OdGeVector3d& axis, float angle);       // rot axis & angle (radian)
////
////        // util functions
////        void        set(float s, float x, float y, float z);
////        void        set(const OdGeVector3d& axis, float angle);  // half angle (radian)
////        float       length() const;                         // compute norm of q
////        Quaternion& normalize();                            // convert it to unit q
////        Quaternion& conjugate();                            // convert it to conjugate
////        Quaternion& invert();                               // convert it to inverse q
////        Matrix4     getMatrix() const;                      // return as 4x4 matrix
////        OdGeVector3d     getVector() const;                      // return as Vector3
////
////        // operators
////        Quaternion  operator-() const;                      // unary operator (negate)
////        Quaternion  operator+(const Quaternion& rhs) const; // addition
////        Quaternion  operator-(const Quaternion& rhs) const; // subtraction
////        Quaternion  operator*(float a) const;               // scalar multiplication
////        Quaternion  operator*(const Quaternion& rhs) const; // multiplication
////        Quaternion  operator*(const OdGeVector3d& v) const;      // conjugation for rotation
////        Quaternion& operator+=(const Quaternion& rhs);      // addition
////        Quaternion& operator-=(const Quaternion& rhs);      // subtraction
////        Quaternion& operator*=(float a);                    // scalar multiplication
////        Quaternion& operator*=(const Quaternion& rhs);      // multiplication
////        bool        operator==(const Quaternion& rhs) const;// exact comparison
////        bool        operator!=(const Quaternion& rhs) const;// exact comparison
////
////        friend Quaternion operator*(const float a, const Quaternion q);
////        friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
////
////        static Quaternion getQuaternion(const OdGeVector3d& v1, const OdGeVector3d& v2);
////        static Quaternion getQuaternion(const OdGeVector2d& angles);
////        static Quaternion getQuaternion(const OdGeVector3d& angles);
////    };
////
////    inline Quaternion::Quaternion(const OdGeVector3d& axis, float angle)
////    {
////        set(axis, angle);
////    }
////
////
////
////    inline void Quaternion::set(float s, float x, float y, float z)
////    {
////        this->s = s;  this->x = x;  this->y = y;  this->z = z;
////    }
////
////
////
////    inline void Quaternion::set(const OdGeVector3d& axis, float angle)
////    {
////        OdGeVector3d v = axis;
////        v.Normalize();
////        float sine = sinf(angle);       // angle is radian
////        s = cosf(angle);
////        x = v.x * sine;
////        y = v.y * sine;
////        z = v.z * sine;
////    }
////
////
////
////    inline float Quaternion::length() const
////    {
////        return sqrtf(s * s + x * x + y * y + z * z);
////    }
////
////
////
////    inline Quaternion& Quaternion::normalize()
////    {
////        const float EPSILON = 0.00001f;
////        float d = s * s + x * x + y * y + z * z;
////        if (d < EPSILON)
////            return *this;
////
////        float invLength = 1.0f / sqrtf(d);
////        s *= invLength;  x *= invLength;  y *= invLength;  z *= invLength;
////        return *this;
////    }
////
////
////
////    inline Quaternion& Quaternion::conjugate()
////    {
////        x = -x;  y = -y;  z = -z;
////        return *this;
////    }
////
////
////
////    inline Quaternion& Quaternion::invert()
////    {
////        const float EPSILON = 0.00001f;
////        float d = s * s + x * x + y * y + z * z;
////        if (d < EPSILON)
////            return *this;
////
////        Quaternion q = *this;
////        *this = q.conjugate() * (1.0f / d);
////        return *this;
////    }
////
////
////
////    inline Matrix4 Quaternion::getMatrix() const
////    {
////        float x2 = x + x;
////        float y2 = y + y;
////        float z2 = z + z;
////        float xx2 = x * x2;
////        float xy2 = x * y2;
////        float xz2 = x * z2;
////        float yy2 = y * y2;
////        float yz2 = y * z2;
////        float zz2 = z * z2;
////        float sx2 = s * x2;
////        float sy2 = s * y2;
////        float sz2 = s * z2;
////
////        return Matrix4(1 - (yy2 + zz2), xy2 + sz2, xz2 - sy2, 0,
////            xy2 - sz2, 1 - (xx2 + zz2), yz2 + sx2, 0,
////            xz2 + sy2, yz2 - sx2, 1 - (xx2 + yy2), 0,
////            0, 0, 0, 1);
////    }
////
////
////
////    inline OdGeVector3d Quaternion::getVector() const
////    {
////        return OdGeVector3d(x, y, z);
////    }
////
////
////
////    inline Quaternion Quaternion::operator-() const
////    {
////        return Quaternion(-s, -x, -y, -z);
////    }
////
////
////
////    inline Quaternion Quaternion::operator+(const Quaternion& rhs) const
////    {
////        return Quaternion(s + rhs.s, x + rhs.x, y + rhs.y, z + rhs.z);
////    }
////
////
////
////    inline Quaternion Quaternion::operator-(const Quaternion& rhs) const
////    {
////        return Quaternion(s - rhs.s, x - rhs.x, y - rhs.y, z - rhs.z);
////    }
////
////
////
////    inline Quaternion Quaternion::operator*(float a) const
////    {
////        return Quaternion(a * s, a * x, a * y, a * z);
////    }
////
////
////
////    inline Quaternion Quaternion::operator*(const Quaternion& rhs) const
////    {
////        OdGeVector3d v1(x, y, z);
////        OdGeVector3d v2(rhs.x, rhs.y, rhs.z);
////
////        OdGeVector3d cross = v1.CrossProduct(v2);
////        float dot = v1.DotProduct(v2);
////        OdGeVector3d v3 = cross + (v2 * s) + (v1 * rhs.s);
////
////        return Quaternion(s * rhs.s - dot, v3.x, v3.y, v3.z);
////    }
////
////
////
////    inline Quaternion Quaternion::operator*(const OdGeVector3d& v) const
////    {
////        Quaternion q(0, x, y, z);
////        return *this * q;
////    }
////
////
////
////    inline Quaternion& Quaternion::operator+=(const Quaternion& rhs)
////    {
////        s += rhs.s;  x += rhs.x;  y += rhs.y;  z += rhs.z;
////        return *this;
////    }
////
////
////
////    inline Quaternion& Quaternion::operator-=(const Quaternion& rhs)
////    {
////        s -= rhs.s;  x -= rhs.x;  y -= rhs.y;  z -= rhs.z;
////        return *this;
////    }
////
////
////
////    inline Quaternion& Quaternion::operator*=(float a)
////    {
////        s *= a;  x *= a;  y *= a; z *= a;
////        return *this;
////    }
////
////
////
////    inline Quaternion& Quaternion::operator*=(const Quaternion& rhs)
////    {
////        *this = *this * rhs;
////        return *this;
////    }
////
////
////
////    inline bool Quaternion::operator==(const Quaternion& rhs) const
////    {
////        return (s == rhs.s) && (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
////    }
////
////
////
////    inline bool Quaternion::operator!=(const Quaternion& rhs) const
////    {
////        return (s != rhs.s) || (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
////    }
////
////    inline Quaternion Quaternion::getQuaternion(const OdGeVector3d& v1, const OdGeVector3d& v2)
////    {
////        const float EPSILON = 0.001f;
////        const float HALF_PI = acos(-1) * 0.5f;
////
////        if (v1.IsEqual(v2))
////        {
////            return Quaternion(v1, 0);
////        }
////        else if (v1.IsEqual(-v2))
////        {
////            OdGeVector3d v;
////            if (v1.x > -EPSILON && v1.x < EPSILON)
////                v = OdGeVector3d(1, 0, 0);
////            else if (v1.y > -EPSILON && v1.y < EPSILON)
////                v = OdGeVector3d(0, 1, 0);
////            else
////                v = OdGeVector3d(0, 0, 1);
////            return Quaternion(v, HALF_PI);
////        }
////
////        OdGeVector3d u1 = v1;
////        OdGeVector3d u2 = v2;
////        u1.Normalize();
////        u2.Normalize();
////
////        OdGeVector3d v = u1.CrossProduct(u2);
////        float angle = acosf(u1.DotProduct(u2));
////        return Quaternion(v, angle * 0.5f);
////    }
////
////
////
////    inline Quaternion Quaternion::getQuaternion(const OdGeVector2d& angles)
////    {
////        Quaternion qx = Quaternion(OdGeVector3d(1, 0, 0), angles.x);
////        Quaternion qy = Quaternion(OdGeVector3d(0, 1, 0), angles.y);
////        return qx * qy;
////    }
////
////    inline Quaternion Quaternion::getQuaternion(const OdGeVector3d& angles)
////    {
////        Quaternion qx = Quaternion(OdGeVector3d(1, 0, 0), angles.x);
////        Quaternion qy = Quaternion(OdGeVector3d(0, 1, 0), angles.y);
////        Quaternion qz = Quaternion(OdGeVector3d(0, 0, 1), angles.z);
////        return qx * qy * qz;
////    }
////
////    inline Quaternion operator*(const float a, const Quaternion& q) {
////        return Quaternion(a * q.s, a * q.x, a * q.y, a * q.z);
////    }
////
////
////    inline std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
////        os << "(" << q.s << ", " << q.x << ", " << q.y << ", " << q.z << ")";
////        return os;
////    }
////}