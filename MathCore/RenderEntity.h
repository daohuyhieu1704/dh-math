#pragma once
#include "ObjectBase.h"

class RenderEntity : public OdObjectBase
{
public:
	ODBASE_DECLARE_MEMBERS(RenderEntity);
	virtual ~RenderEntity() = default;
	virtual void render() = 0;
};

typedef OdSmartPtr<RenderEntity> RenderEntityPtr;