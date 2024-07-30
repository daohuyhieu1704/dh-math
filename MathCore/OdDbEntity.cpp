#include "pch.h"
#include "OdDbEntity.h"

OdGeExtend2d OdDbEntity::GetBoundary() const
{
	return m_boundary;
}

void OdDbEntity::SetBoundary(OdGeExtend2d boundary)
{
	m_boundary = boundary;
}

OdObjectBase* OdDbEntity::Clone() const
{
	return nullptr;
}
