#include "pch.h"
#include "OdDbObject.h"

ODBASE_DXF_DEFINE_MEMBERS(OdDbObject, OdDrawable, DBOBJECT_CONSTR, AiDbObject, Object)
   OdDbObject::OdDbObject()
{
}

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