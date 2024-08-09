#include "pch.h"
#include "CircleJig.h"

namespace MathGL
{
	CircleJig::CircleJig() : Jig(new GLCircleJig())
	{
	}

	CircleJig::CircleJig(Geom::Point3d centerPnt) : Jig(new GLCircleJig(centerPnt.ToNative()))
	{
	}
}