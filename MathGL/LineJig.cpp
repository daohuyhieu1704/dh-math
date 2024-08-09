#include "pch.h"
#include "LineJig.h"

namespace MathGL
{
	LineJig::LineJig() : Jig(new GLLineJig())
	{
	}
	LineJig::LineJig(Geom::Point3d startPnt) : Jig(new GLLineJig(startPnt.ToNative()))
	{
	}
}
