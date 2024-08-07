#include "pch.h"
#include "PromptPointSelection.h"
#include "GLEngineNative.h"

OdGePoint3d PromptPointSelection::getPoints()
{
	auto points = GLEngineNative::GetInstance()->points;
	if (points.size() == 0)
	{
		return OdGePoint3d(0.0, 0.0, 0.0);
	}
	OdGePoint2d lastPoint = points[points.size() - 1];
    return OdGePoint3d(lastPoint.x, lastPoint.y, 0.0);
}


void PromptPointSelection::Focus()
{
}