#pragma once
#include "OdGePoint2d.h"

using namespace System;
using namespace Geometry;

namespace MathCore
{
	namespace Geom
	{
		public value class Point2d
		{
        private:
            float x;
            float y;

        public:
            Point2d(float x, float y) : x(x), y(y) {}

            property float X
            {
                float get()
                {
                    return x;
                }
                void set(float value)
                {
                    x = value;
                }
            }

            property float Y
            {
                float get()
                {
                    return y;
                }
                void set(float value)
                {
                    y = value;
                }
            }

            OdGePoint2d ToNative()
            {
                return OdGePoint2d(x, y);
            }

            static Point2d FromNative(OdGePoint2d point)
            {
                return Point2d(point.x, point.y);
            }

			String^ ToString() override
			{
				return String::Format("{0},{1}", x, y);
			}
		};
	}
}

