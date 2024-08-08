#pragma once
#include <PromptPointSelection.h>
#include <Point3d.h>
#include "DisposableWrapper.h"

using namespace MathCore::Geom;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

namespace MathGL
{
	public delegate void DoublePickedDelegate(double resVal);
	public delegate void DoubleSelectedCallback(double value);

	public ref class DoubleSelection
	{
	public:
		~DoubleSelection();
		DoubleSelection();
		Task<double>^ getDouble();
	private:
		static void OnPointPicked(double resPnt)
		{
			_tcs->SetResult(resPnt);
		}

		static DoublePickedDelegate^ _doublePickedDelegate;
		static TaskCompletionSource<double>^ _tcs;
	};

}
