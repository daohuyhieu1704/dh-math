#include "pch.h"
#include "OdDbObject.h"

nlohmann::json OdDbObject::ToJson() const
{
    return
    {
        {"position", {m_position.x, m_position.y}},
        {"rotation", m_rotation},
    };
}