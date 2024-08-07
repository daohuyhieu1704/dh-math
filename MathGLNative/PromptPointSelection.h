#pragma once
#include <vector>
#include <OdGePoint3d.h>
using namespace Geometry;

class PromptPointSelection
{

public:
    using PointPickedCallback = void(*)(double x, double y, double z);
    OdGePoint3d getPoints();
    void Focus();
};

