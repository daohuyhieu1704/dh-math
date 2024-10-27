#pragma once
#include "OdGeMatrix3d.h"
#include <cmath> 

namespace Geometry
{
	class OdGeScale3d
	{
	public:
		/** \details
		  Default constructor for the OdGeScale3d class.

		  \remarks
		  Constructs the scale object with 1.0 for scale factor for each axis.
		*/
		OdGeScale3d() : sx(1.0), sy(1.0), sz(1.0) {}

		/** \details
		  Constructor for the OdGeScale3d class.

		  \param factor [in]  Uniform scale factor.

		  \remarks
		  The constructor constructs a unified scale factor with the specified double value.
		*/
		OdGeScale3d(double factor) : sx(factor), sy(factor), sz(factor) {}

		/** \details
		  Constructor for the OdGeScale3d class.

		  \param xFactor [in]  The X scale factor.
		  \param yFactor [in]  The Y scale factor.
		  \param zFactor [in]  The Z scale factor.

		  \remarks
		  The constructor constructs scale transformation with the specified factors for X, Y, Z axes.
		*/
		OdGeScale3d(double xFactor, double yFactor, double zFactor)
			: sx(xFactor), sy(yFactor), sz(zFactor) {}

		// Multiplicative identity vector.
		static const OdGeScale3d kIdentity;

		OdGeScale3d operator *(const OdGeScale3d& scaleVec) const
		{
			return OdGeScale3d(sx * scaleVec.sx, sy * scaleVec.sy, sz * scaleVec.sz);
		}

		OdGeScale3d operator *(double factor) const
		{
			return OdGeScale3d(sx * factor, sy * factor, sz * factor);
		}

		friend OdGeScale3d operator *(double factor, const OdGeScale3d& scaleVec)
		{
			return OdGeScale3d(factor * scaleVec.sx, factor * scaleVec.sy, factor * scaleVec.sz);
		}

		OdGeScale3d& operator *=(const OdGeScale3d& scaleVec)
		{
			sx *= scaleVec.sx;
			sy *= scaleVec.sy;
			sz *= scaleVec.sz;
			return *this;
		}

		OdGeScale3d& operator *=(double factor)
		{
			sx *= factor;
			sy *= factor;
			sz *= factor;
			return *this;
		}

		OdGeScale3d& setToProduct(const OdGeScale3d& scaleVec1, const OdGeScale3d& scaleVec2)
		{
			sx = scaleVec1.sx * scaleVec2.sx;
			sy = scaleVec1.sy * scaleVec2.sy;
			sz = scaleVec1.sz * scaleVec2.sz;
			return *this;
		}

		OdGeScale3d& setToProduct(const OdGeScale3d& scaleVec, double factor)
		{
			sx = scaleVec.sx * factor;
			sy = scaleVec.sy * factor;
			sz = scaleVec.sz * factor;
			return *this;
		}

		OdGeScale3d inverse() const
		{
			return OdGeScale3d(1.0 / sx, 1.0 / sy, 1.0 / sz);
		}

		OdGeScale3d& invert()
		{
			sx = 1.0 / sx;
			sy = 1.0 / sy;
			sz = 1.0 / sz;
			return *this;
		}

		bool isProportional() const
		{
			return (sx == sy && sy == sz);
		}

		bool operator ==(const OdGeScale3d& scaleVec) const
		{
			return (sx == scaleVec.sx && sy == scaleVec.sy && sz == scaleVec.sz);
		}

		bool operator !=(const OdGeScale3d& scaleVec) const
		{
			return !(*this == scaleVec);
		}

		bool isEqualTo(const OdGeScale3d& scaleVec, double tol = 1e-9) const
		{
			return (std::abs(sx - scaleVec.sx) <= tol &&
				std::abs(sy - scaleVec.sy) <= tol &&
				std::abs(sz - scaleVec.sz) <= tol);
		}

		double& operator [](unsigned int i)
		{
			return (i == 0) ? sx : (i == 1) ? sy : sz;
		}

		double operator [](unsigned int i) const
		{
			return (i == 0) ? sx : (i == 1) ? sy : sz;
		}

		OdGeScale3d& set(double xFactor, double yFactor, double zFactor)
		{
			sx = xFactor;
			sy = yFactor;
			sz = zFactor;
			return *this;
		}

		void getMatrix(OdGeMatrix3d& xfm) const
		{
			// Set the matrix as a scaling matrix with sx, sy, and sz
			xfm.setToIdentity();
			//xfm(0, 0) = sx;
			//xfm(1, 1) = sy;
			//xfm(2, 2) = sz;
		}

		OdGeScale3d& extractScale(const OdGeMatrix3d& xfm)
		{
			// Extract the scaling factors from the matrix
			//sx = xfm(0, 0);
			//sy = xfm(1, 1);
			//sz = xfm(2, 2);
			return *this;
		}

		OdGeScale3d& removeScale(OdGeMatrix3d& xfm, bool negateX = false)
		{
			// Remove scaling from the matrix
			//sx = xfm(0, 0);
			//sy = xfm(1, 1);
			//sz = xfm(2, 2);

			//// Reset scale components to 1
			//xfm(0, 0) = (negateX ? -1.0 : 1.0);
			//xfm(1, 1) = 1.0;
			//xfm(2, 2) = 1.0;
			return *this;
		}

		operator OdGeMatrix3d() const
		{
			OdGeMatrix3d xfm;
			getMatrix(xfm);
			return xfm;
		}

		bool isValid() const
		{
			return (sx != 0.0 && sy != 0.0 && sz != 0.0);
		}

	private:
		double sx; // X scale factor.
		double sy; // Y scale factor.
		double sz; // Z scale factor.
	};

	// Define the identity scale vector
	const OdGeScale3d OdGeScale3d::kIdentity = OdGeScale3d(1.0, 1.0, 1.0);
}