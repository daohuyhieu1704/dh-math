#pragma once
#include "OdObjectBase.h"
#include "OdPrValue.h"
#include "OdPrProperty.h"

class OdPrAttributeImpl;
class OdPrAttributeCollectionImpl;
class OdPrMember;
class OdPrPropertyBase;

class OdBaseAttribute :
    public OdObjectBase
{
	std::string m_name;
	std::string m_value;
public:
    ODBASE_DECLARE_MEMBERS(OdBaseAttribute);  
    virtual ~OdBaseAttribute();
protected:
    //DOM-IGNORE-BEGIN
    OdBaseAttribute(std::string m_name, std::string value);
    friend class OdPrAttributeImpl;
public:
	std::string name() const;
	void setName(const std::string& name);
};

typedef OdSmartPtr<OdBaseAttribute> OdBaseAttributePtr;