#pragma once
#include "OdDbEntity.h"
#include "OdGePoint2d.h"

class OdDbSquare : public OdDbEntity
{
private:
    OdGePoint2d m_minPnt;
    OdGePoint2d m_maxPnt;
    double m_height;

public:
    OdDbSquare();
    ~OdDbSquare();

    OdGePoint2d getMinPnt() const;
    virtual void setMinPnt(OdGePoint2d minPnt);

    OdGePoint2d getMaxPnt() const;
    virtual void setMaxPnt(OdGePoint2d maxPnt);

    double getHeight() const;
    virtual void setHeight(double height);

    nlohmann::json ToJson() const override;
    void WorldDraw() override;
};
