#include "pch.h"
#include "OdDbEntity.h"


ODBASE_DXF_DEFINE_MEMBERS(OdDbEntity, OdDbObject, DBOBJECT_CONSTR, AiEntity, Entity)

OdGeExtents3d OdDbEntity::GetBoundary() const
{
	return m_boundary;
}

void OdDbEntity::SetBoundary(OdGeExtents3d boundary)
{
	m_boundary = boundary;
}

double OdDbEntity::getSphereRadius()
{
	return m_boundary.GetMaxPnt().DistanceTo((m_boundary.GetMinPnt())) / 2;
}

bool OdDbEntity::getIsSelected() const
{
	return m_isSelected;

}
void OdDbEntity::setIsSelected(bool isSelected)
{
	m_isSelected = isSelected;
}
std::string OdDbEntity::getShape() const
{
	return m_shape;
}
void OdDbEntity::setShape(std::string shape)
{
	m_shape = shape;
}
OdGePoint3d OdDbEntity::getCenter() const
{
	return m_boundary.getCenter();
}