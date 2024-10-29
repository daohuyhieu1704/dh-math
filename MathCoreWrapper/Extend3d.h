#pragma once
#include "OdGeExtents3d.h"
#include "Point3d.h"

using namespace System;

namespace MathCore
{
    namespace Geom
    {
        public value class Extend3d
        {
        private:
            Point3d minPnt;
			Point3d maxPnt;

        public:
            Extend3d(Point3d minPnt, Point3d maxPnt)
            {
				this->minPnt = minPnt;
				this->maxPnt = maxPnt;
            }

            property Point3d MinPnt
            {
                Point3d get()
                {
					return minPnt;
                }
                void set(Point3d value)
                {
					minPnt = value;
                }
            }

            property Point3d MaxPnt
            {
                Point3d get()
                {
					return maxPnt;
                }
                void set(Point3d value)
                {
					maxPnt = value;
                }
            }

            OdGeExtents3d ToNative()
            {
				return OdGeExtents3d(minPnt.ToNative(), maxPnt.ToNative());
            }

            static Extend3d FromNative(OdGeExtents3d nativeExtend)
            {
				return Extend3d(Point3d::FromNative(nativeExtend.GetMinPnt()), Point3d::FromNative(nativeExtend.GetMaxPnt()));
            }

            String^ ToString() override
            {
                return String::Format("{0},{1}", MinPnt.ToString(), MaxPnt.ToString());
            }
        };
    }
}
