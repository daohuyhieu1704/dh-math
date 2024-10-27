#pragma once
#include "ObjectBase.h"
#include "OdGePoint3d.h"
#include "RenderEntity.h"
#include <vector>
#include "OdGeExtents3d.h"

using namespace Geometry;

class OdDbStub;

class OdDrawable : public OdObjectBase {
protected:
    OdDrawable() : OdObjectBase(), m_position(0, 0, 0), m_rotation(0), m_renderMethod(nullptr) {
        m_color[0] = 1.0f;
        m_color[1] = 1.0f;
        m_color[2] = 1.0f;
        m_color[3] = 1.0f;
    }
public:

    ODBASE_DECLARE_MEMBERS(OdDrawable);
    RenderEntity* m_renderMethod;
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

    /** \details
      Checks whether this object is persistent (stored in a database).
    
      \returns
      true this object is persistent (stored in a database), false otherwise.
    */
    virtual bool isPersistent() const = 0;

    /** \details
  Retrieves the database ID of this object.

  \returns
  pointer to OdDbStub which represents a database identifier of this object.

  \remarks
  Returns a null pointer if this object is not persistent.
*/
    virtual OdDbStub* id() const = 0;
    virtual OdResult getGeomExtents(OdGeExtents3d& extents) const;
    OdGePoint3d m_position;
private:
    float m_rotation;
    float m_color[4];
};

typedef OdSmartPtr<OdDrawable> OdDrawablePtr;