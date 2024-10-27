#include "pch.h"
#include "OdDbObject.h"

ODBASE_DEFINE_RTTI_MEMBERS_GENERIC(OdDbObject, OdDbObject, OdDrawable)

void OdDbObject::addRef()
{
}

void OdDbObject::release()
{
}

long OdDbObject::numRefs() const
{
    return 0;
}

nlohmann::json OdDbObject::ToJson() const
{
    //return
    //{
    //    {"position", {m_position.x, m_position.y}},
    //    {"rotation", m_rotation},
    //};
     return
    {
        {"position", {1, 1}},
        {"rotation", 1},
    };
}