#include "pch.h"
#include "PointSelection.h"
#include "GLEngineNative.h"

namespace MathGL
{
	PointSelection::~PointSelection()
	{
		GLEngineNative::GetInstance()->points.clear();
	}

	PointSelection::PointSelection() : DisposableWrapper(System::IntPtr(new PromptPointSelection()), true)
	{
		GLEngineNative::GetInstance()->points.clear();
	}

	Task<List<Point3d>^>^ PointSelection::getPoints(int total)
	{
        GLEngineNative::GetInstance()->m_totalPick = total;
        GLEngineNative::GetInstance()->pointPicked = true;
        _tcs = gcnew TaskCompletionSource<List<Point3d>^>();

        _pointPickedDelegate = gcnew PointPickedDelegate(&PointSelection::OnPointPicked);

        IntPtr ptr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_pointPickedDelegate);
        GLEngineNative::GetInstance()->SetPointPickedCallback(static_cast<PointPickedCallback>(ptr.ToPointer()));

		return _tcs->Task;
	}

	Point3d PointSelection::getPoint()
	{
		auto points = GLEngineNative::GetInstance()->points;
		if (points.size() == 0)
		{
			return Point3d(0.0, 0.0, 0.0);
		}
		OdGePoint2d lastPoint = points[points.size() - 1];
		return Point3d(lastPoint.x, lastPoint.y, 0.0);
	}

	PromptPointSelection* PointSelection::GetImpObj()
	{
		void* obj = DisposableWrapper::GetImpObj();
		return static_cast<PromptPointSelection*>(obj);
	}
}