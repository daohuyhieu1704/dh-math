#pragma once
#include <OdGePoint3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Geometry;

class APIGLConverter
{
public:
	static glm::vec3 OdGePoint3dToVec3(const OdGePoint3d& point);
};

