#pragma once
#include "OdGePoint3d.h"

namespace Geometry
{
    class OdGeExtend3d
    {
    private:
        OdGePoint3d m_minPnt;
        OdGePoint3d m_maxPnt;

    public:
        OdGeExtend3d(OdGePoint3d minPnt, OdGePoint3d maxPnt)
            : m_minPnt(minPnt), m_maxPnt(maxPnt) {}

        ~OdGeExtend3d() {}

#pragma region Properties

        OdGePoint3d GetMinPnt() const { return m_minPnt; }
        void SetMinPnt(OdGePoint3d minPnt) { m_minPnt = minPnt; }

        OdGePoint3d GetMaxPnt() const { return m_maxPnt; }
        void SetMaxPnt(OdGePoint3d maxPnt) { m_maxPnt = maxPnt; }

#pragma endregion
    };
}
