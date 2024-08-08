#include "pch.h"
#include "DoubleSelection.h"

namespace MathGL
{
	DoubleSelection::~DoubleSelection()
	{
		throw gcnew System::NotImplementedException();
	}

	DoubleSelection::DoubleSelection()
	{
		throw gcnew System::NotImplementedException();
	}
	Task<double>^ DoubleSelection::getDouble()
	{
	/*	GLEngineNative::GetInstance()->m_totalPick = total;
		GLEngineNative::GetInstance()->pointPicked = true;
		_tcs = gcnew TaskCompletionSource<List<Point3d>^>();

		_pointPickedDelegate = gcnew PointPickedDelegate(&DoubleSelection::OnPointPicked);

		IntPtr ptr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_pointPickedDelegate);
		GLEngineNative::GetInstance()->SetPointPickedCallback(static_cast<PointPickedCallback>(ptr.ToPointer()));*/

		return _tcs->Task;
	}
}