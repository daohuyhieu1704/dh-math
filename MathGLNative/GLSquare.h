#pragma once
#include "RenderEntity.h"
#include "OdGePoint2d.h"

using namespace Geometry;

class GLSquare : public RenderEntity
{
private:
    OdGePoint2d m_minPnt;
    OdGePoint2d m_maxPnt;
    double m_height;

public:
#pragma region Properties
    ODBASE_DECLARE_MEMBERS(GLSquare);
    OdGePoint2d getMinPnt() const;
    void setMinPnt(OdGePoint2d minPnt);

    OdGePoint2d getMaxPnt() const;
    void setMaxPnt(OdGePoint2d maxPnt);

    double getHeight() const;
    void setHeight(double height);
#pragma endregion

    void render() override;
    ~GLSquare() {}
};
