#pragma once
#include "ObjectBase.h"
#include "OdGePoint3d.h"
#include "RenderEntity.h"
#include <vector>
#include "OdGeExtents3d.h"

using namespace Geometry;

class OdDrawable : public OdObjectBase {
protected:
    OdDrawable();
public:
    ODBASE_DECLARE_MEMBERS(OdDrawable);
    RenderEntityPtr m_renderMethod;
    virtual ~OdDrawable() = default;

#pragma region Properties
    void setDefaults();
    OdGePoint3d GetPosition() const;
    void SetPosition(OdGePoint3d pos);
    void SetPosition(float x, float y);
    float GetRotation() const;
    void SetRotation(float rot);
    void GetColor(float* color) const;
    std::vector<float> GetColor() const;
    void SetColor(float red, float green, float blue, float alpha);
#pragma endregion
    virtual OdResult getGeomExtents(OdGeExtents3d& extents) const;
    OdGePoint3d m_position;
private:
    float m_rotation;
    float m_color[4];
};

typedef OdSmartPtr<OdDrawable> OdDrawablePtr;