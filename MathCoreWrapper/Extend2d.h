#pragma once
#include "OdGeExtend2d.h"
#include "Point2d.h"

using namespace System;
namespace MathCore
{
namespace Geom
{
    public value class Extend2d
    {
    private:
        Point2d minPnt;
        Point2d maxPnt;
    public:
        Extend2d(Point2d minPnt, Point2d maxPnt)
        {
			this->minPnt = minPnt;
			this->maxPnt = maxPnt;
        }

        property Point2d MinPnt
        {
            Point2d get()
            {
				return minPnt;
            }
            void set(Point2d value)
            {
				minPnt = value;
            }
        }

		property Point2d MaxPnt
		{
            Point2d get()
            {
				return maxPnt;
            }
            void set(Point2d value)
            {
				maxPnt = value;
            }
		}

        OdGeExtend2d ToNative()
        {
			return OdGeExtend2d(minPnt.ToNative(), maxPnt.ToNative());
        }

        static Extend2d FromNative(OdGeExtend2d point)
		{
			return Extend2d(Point2d::FromNative(point.GetMinPnt()), Point2d::FromNative(point.GetMaxPnt()));
        }

        String^ ToString() override
        {
			return String::Format("{0},{1}", MinPnt.ToString(), MaxPnt.ToString());
        }
    };
}
}