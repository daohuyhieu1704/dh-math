#pragma once

#include "OdDbObject.h"
#include "OdGeExtents3d.h"
#include "OdGePoint2d.h"

using namespace Geometry;

class OdDbEntity : public OdDbObject
{
public:
    ODBASE_DECLARE_MEMBERS(OdDbEntity);
protected:
    OdGeExtents3d m_boundary;
    bool m_isSelected = false;
    std::string m_shape;
public:
    OdDbEntity() : OdDbObject(), m_boundary(OdGeExtents3d(OdGePoint3d({ 0, 0, 0 }), OdGePoint3d({ 0, 0, 0 }))), m_shape("Entity") {}
#pragma region Properties
    OdGeExtents3d GetBoundary() const;
    void SetBoundary(OdGeExtents3d boundary);
    double getSphereRadius();
	bool getIsSelected() const;
	void setIsSelected(bool isSelected);
	std::string getShape() const;
	void setShape(std::string shape);
	OdGePoint3d getCenter() const;
#pragma endregion
    virtual void WorldDraw() = 0;
    virtual ~OdDbEntity() = default;
};
