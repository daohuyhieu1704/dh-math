#pragma once
#include "RenderEntity.h"
#include "OdGePoint3d.h"

using namespace Geometry;

class GLCircle : public RenderEntity
{
private:
    OdGePoint3d m_center;
    double m_radius;
    int num_segments = 1000;
public:
#pragma region Properties
    OdGePoint3d getCenter() const;
    void setCenter(OdGePoint3d center);

    double getRadius() const;
    void setRadius(double radius);
#pragma endregion

    void render() override;
    ~GLCircle() {}
};