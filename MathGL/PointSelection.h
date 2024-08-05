#pragma once
#include <PromptPointSelection.h>
#include <Point3d.h>
#include "DisposableWrapper.h"

using namespace MathCore::Geom;

public ref class PointSelection : MathCore::DisposableWrapper
{
public:
	~PointSelection();
	PointSelection();
	Point3d getPoints(int total);
private:
	PromptPointSelection* GetImpObj();
};

