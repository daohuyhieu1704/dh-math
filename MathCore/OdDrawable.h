#pragma once
#include "OdObjectBase.h"
#include "OdGePoint3d.h"
#include "RenderEntity.h"
#include <vector>

using namespace Geometry;

class OdDrawable : public OdObjectBase {
protected:
    OdGePoint3d m_position;
    float m_rotation;
    float m_color[4];
public:
    RenderEntity* m_renderMethod;
    OdDrawable() : OdObjectBase(), m_position(0, 0, 0), m_rotation(0), m_renderMethod(nullptr) {
        m_color[0] = 1.0f;
        m_color[1] = 1.0f;
        m_color[2] = 1.0f;
        m_color[3] = 1.0f;
    }
    virtual ~OdDrawable() = default;

#pragma region Properties
    OdGePoint3d GetPosition() const;
    void SetPosition(OdGePoint3d pos);
    void SetPosition(float x, float y);
    float GetRotation() const;
    void SetRotation(float rot);
    void GetColor(float* color) const;
    std::vector<float> GetColor() const;
    void SetColor(float red, float green, float blue, float alpha);
#pragma endregion
    virtual OdObjectBasePtr Clone() const = 0;
};
