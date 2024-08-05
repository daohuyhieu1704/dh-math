#include "pch.h"
#include "PointSelection.h"
#include "GLEngineNative.h"

PointSelection::~PointSelection()
{
}

PointSelection::PointSelection() : DisposableWrapper(System::IntPtr(new PromptPointSelection()), true)
{
}

Point3d PointSelection::getPoints(int total)
{
	if (GLEngineNative::GetInstance()->points.size() == total)
	{
		OdGePoint3d point = GetImpObj()->getPoints();
		return Point3d(point.x, point.y, point.z);
	}
}

PromptPointSelection* PointSelection::GetImpObj()
{
	void* obj = DisposableWrapper::GetImpObj();
	return static_cast<PromptPointSelection*>(obj);
}
