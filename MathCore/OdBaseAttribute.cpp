#include "pch.h"
#include "OdBaseAttribute.h"

OdBaseAttribute::~OdBaseAttribute()
{
}

OdBaseAttribute::OdBaseAttribute(std::string m_name, std::string value)
{
	m_name = m_name;
	m_value = value;
}

std::string OdBaseAttribute::name() const
{
	return m_name;
}

void OdBaseAttribute::setName(const std::string& name)
{
	m_name = name;
}
