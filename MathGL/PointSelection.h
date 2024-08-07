#pragma once
#include <PromptPointSelection.h>
#include <Point3d.h>
#include "DisposableWrapper.h"

using namespace MathCore::Geom;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

namespace MathGL
{
	public delegate void PointPickedDelegate(std::vector<Geometry::OdGePoint2d> resPnt);
	public delegate void PointsSelectedCallback(List<Point3d>^ points);

	public ref class PointSelection : MathCore::DisposableWrapper
	{
	public:
		~PointSelection();
		PointSelection();
		Task<List<Point3d>^>^ getPoints(int total);
		Point3d getPoint();
	private:
		PromptPointSelection* GetImpObj();    
		static void OnPointPicked(std::vector<Geometry::OdGePoint2d> resPnt)
		{
			List<Point3d>^ points = gcnew List<Point3d>(resPnt.size());
			for (int i = 0; i < resPnt.size(); i++)
			{
				points->Add(Point3d(resPnt[i].x, resPnt[i].y, 0.0));
			}

			_tcs->SetResult(points);
		}

		static PointPickedDelegate^ _pointPickedDelegate;
		static TaskCompletionSource<List<Point3d>^>^ _tcs;
	};

}
