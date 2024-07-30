#pragma once
#include "OdDbEntity.h"

enum DragStatus {
    kNormal = 0,
    kCancel = 1,
    kOther = 2,
    kNoChange = 3
};

class OdJig
{
public:
    virtual ~OdJig() {}
    virtual OdDbEntity* entity() const = 0;
    virtual DragStatus sampler() = 0;
    virtual bool update() = 0;
    virtual bool Preview(void* renderTarget) = 0;
    virtual DragStatus AcquirePoint(OdGePoint3d& point) = 0;
};

