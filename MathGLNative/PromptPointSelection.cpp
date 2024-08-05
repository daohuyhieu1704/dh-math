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
	std::pair<GLfloat, GLfloat> lastPoint = points[points.size() - 1];
    return OdGePoint3d(lastPoint.first, lastPoint.second, 0.0);
}
