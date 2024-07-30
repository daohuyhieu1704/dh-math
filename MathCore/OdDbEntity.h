#pragma once

#include "OdDbObject.h"
#include "OdGeExtend2d.h"
#include "OdGePoint2d.h"

using namespace Geometry;

class OdDbEntity : public OdDbObject
{
private:
    OdGeExtend2d m_boundary;
public:
    OdDbEntity() : OdDbObject(), m_boundary(OdGeExtend2d(OdGePoint2d({ 0,0 }), OdGePoint2d({ 0,0 }))) {}
#pragma region Properties
    OdGeExtend2d GetBoundary() const;
    void SetBoundary(OdGeExtend2d boundary);
#pragma endregion
    virtual void WorldDraw() = 0;
    OdObjectBase* Clone() const override;
    virtual ~OdDbEntity() = default;
};
