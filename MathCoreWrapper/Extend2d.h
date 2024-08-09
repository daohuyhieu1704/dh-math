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
        OdGeExtend2d* m_pExtend2d;
    public:
        Extend2d(Point2d minPnt, Point2d maxPnt)
        {
            m_pExtend2d = new OdGeExtend2d(minPnt.ToNative(), maxPnt.ToNative());
        }

        property Point2d MinPnt
        {
            Point2d get()
            {
                return Point2d::FromNative(m_pExtend2d->GetMinPnt());
            }
            void set(Point2d value)
            {
                m_pExtend2d->SetMinPnt(value.ToNative());
            }
        }

        property Point2d MaxPnt
        {
			Point2d get()
			{
				return Point2d::FromNative(m_pExtend2d->GetMaxPnt());
			}
			void set(Point2d value)
			{
				m_pExtend2d->SetMaxPnt(value.ToNative());
			}
        }

        OdGeExtend2d ToNative()
        {
			return *m_pExtend2d;
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