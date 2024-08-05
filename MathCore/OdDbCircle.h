#pragma once
#include "OdDbEntity.h"

class OdDbCircle :
    public OdDbEntity
{
    OdGePoint3d m_center;
    double m_radius;
public:
    OdDbCircle();
    ~OdDbCircle();

    virtual OdGePoint3d getCenter() const;
    virtual void setCenter(OdGePoint3d center);

    virtual double getRadius() const;
    virtual void setRadius(double radius);

    nlohmann::json ToJson() const override;
    void WorldDraw() override;
};

