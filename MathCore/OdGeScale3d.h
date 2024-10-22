#pragma once
#include "OdGeTol.h"

class OdGeMatrix3d;

class OdGeScale3d
{
    OdGeScale3d() : sx(1.0), sy(1.0), sz(1.0) {}

    // Constructor with uniform scale factor
    OdGeScale3d(double factor) : sx(factor), sy(factor), sz(factor) {}

    // Constructor with specific scale factors for X, Y, Z
    OdGeScale3d(double xFactor, double yFactor, double zFactor)
        : sx(xFactor), sy(yFactor), sz(zFactor) {}

    // Identity scale (kIdentity)
    static const OdGeScale3d kIdentity;

    // Multiplication with another scale vector
    OdGeScale3d operator*(const OdGeScale3d& scaleVec) const {
        return OdGeScale3d(sx * scaleVec.sx, sy * scaleVec.sy, sz * scaleVec.sz);
    }

    // Multiplication with a uniform scale factor
    OdGeScale3d operator*(double factor) const {
        return OdGeScale3d(sx * factor, sy * factor, sz * factor);
    }

    // Multiplication with scale vector and assignment
    OdGeScale3d& operator*=(const OdGeScale3d& scaleVec) {
        sx *= scaleVec.sx;
        sy *= scaleVec.sy;
        sz *= scaleVec.sz;
        return *this;
    }

    // Multiplication with uniform scale factor and assignment
    OdGeScale3d& operator*=(double factor) {
        sx *= factor;
        sy *= factor;
        sz *= factor;
        return *this;
    }

    // Pre-multiply with another scale vector
    OdGeScale3d& preMultBy(const OdGeScale3d& leftSide) {
        return operator*=(leftSide);
    }

    // Post-multiply with another scale vector
    OdGeScale3d& postMultBy(const OdGeScale3d& rightSide) {
        return operator*=(rightSide);
    }

    // Set this scale vector to the product of two scale vectors
    OdGeScale3d& setToProduct(const OdGeScale3d& scaleVec1, const OdGeScale3d& scaleVec2) {
        sx = scaleVec1.sx * scaleVec2.sx;
        sy = scaleVec1.sy * scaleVec2.sy;
        sz = scaleVec1.sz * scaleVec2.sz;
        return *this;
    }

    // Set this scale vector to the product of a factor and a scale vector
    OdGeScale3d& setToProduct(const OdGeScale3d& scaleVec, double factor) {
        sx = scaleVec.sx * factor;
        sy = scaleVec.sy * factor;
        sz = scaleVec.sz * factor;
        return *this;
    }

    // Return the inverse of this scale vector
    OdGeScale3d inverse() const {
        return OdGeScale3d(1.0 / sx, 1.0 / sy, 1.0 / sz);
    }

    // Invert this scale vector
    OdGeScale3d& invert() {
        sx = 1.0 / sx;
        sy = 1.0 / sy;
        sz = 1.0 / sz;
        return *this;
    }

    // Check if this scale vector is proportional to another one
    bool isProportional(const OdGeTol& tol = OdGeContext::gTol) const {
        return (std::abs(sx - sy) <= tol.equalPoint() && std::abs(sx - sz) <= tol.equalPoint());
    }

    // Equality operator
    bool operator==(const OdGeScale3d& scaleVec) const {
        return (sx == scaleVec.sx && sy == scaleVec.sy && sz == scaleVec.sz);
    }

    // Inequality operator
    bool operator!=(const OdGeScale3d& scaleVec) const {
        return !(*this == scaleVec);
    }

    // Check if scale vectors are equal within a tolerance
    bool isEqualTo(const OdGeScale3d& scaleVec, const OdGeTol& tol = OdGeContext::gTol) const {
        return (std::abs(sx - scaleVec.sx) <= tol.equalPoint() &&
            std::abs(sy - scaleVec.sy) <= tol.equalPoint() &&
            std::abs(sz - scaleVec.sz) <= tol.equalPoint());
    }

    // Index operator (read-only)
    double operator[](unsigned int i) const {
        return *(&sx + i);
    }

    // Index operator (modifiable)
    double& operator[](unsigned int i) {
        return *(&sx + i);
    }

    // Set scale factors for X, Y, Z
    OdGeScale3d& set(double xFactor, double yFactor, double zFactor) {
        sx = xFactor;
        sy = yFactor;
        sz = zFactor;
        return *this;
    }

    // Conversion to matrix
    operator OdGeMatrix3d() const {
        OdGeMatrix3d mat;
        mat.setToScaling(OdGeScale3d(sx, sy, sz));
        return mat;
    }

    // Get equivalent transformation matrix
    void getMatrix(OdGeMatrix3d& xfm) const {
        xfm.setToScaling(*this);
    }

    // Extract scale from a matrix
    OdGeScale3d& extractScale(const OdGeMatrix3d& xfm) {
        // Logic to extract the scale factors from the matrix
        // assuming the matrix is orthogonally scaled
        sx = xfm[0].length();
        sy = xfm[1].length();
        sz = xfm[2].length();
        return *this;
    }

    // Remove scale from matrix
    OdGeScale3d& removeScale(OdGeMatrix3d& xfm, bool negateX = false) {
        // Logic to remove the scaling from the matrix
        OdGeScale3d scale = extractScale(xfm);
        xfm.setToScaling(OdGeScale3d(1, 1, 1));
        return *this;
    }

    // Check if scale vector is valid
    bool isValid() const {
        return OdNonZero(sx) && OdNonZero(sy) && OdNonZero(sz);
    }

    double sx; // X scale factor
    double sy; // Y scale factor
    double sz; // Z scale factor
};

