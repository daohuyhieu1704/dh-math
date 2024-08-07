#pragma once
#include <OdGePoint3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Geometry;

class APIGLConverter
{
public:
	static glm::vec3 OdGePoint3dToVec3(const OdGePoint3d& point);
	static OdGePoint3d Vec3ToOdGePoint3d(const glm::vec3& vec);
	static glm::vec3 OdGeVector3dToVec3(const OdGeVector3d& vector);
};

