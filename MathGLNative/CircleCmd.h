#pragma once
#include <IActionCmd.h>
#include <OdGePoint3d.h>

using namespace Geometry;

class CircleCmd :
    public IActionCmd
{
public:
    CircleCmd() : center{ 0, 0, 0 }, radius(0) {}

    void serialize(const std::vector<std::string>& strData) override;
    bool execute() override;

private:
    OdGePoint3d center;
    double radius;
};

