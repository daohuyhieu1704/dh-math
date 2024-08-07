#include "pch.h"
#include "APIGLConverter.h"

glm::vec3 APIGLConverter::OdGePoint3dToVec3(const OdGePoint3d& point)
{
	return glm::vec3(point.x, point.y, point.z);
}
