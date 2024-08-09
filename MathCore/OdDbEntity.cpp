#include "pch.h"
#include "OdDbEntity.h"

OdGeExtend3d OdDbEntity::GetBoundary() const
{
	return m_boundary;
}

void OdDbEntity::SetBoundary(OdGeExtend3d boundary)
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
OdObjectBase* OdDbEntity::Clone() const
{
	return nullptr;
}
