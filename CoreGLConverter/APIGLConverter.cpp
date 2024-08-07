#include "pch.h"
#include "APIGLConverter.h"

glm::vec3 APIGLConverter::OdGePoint3dToVec3(const OdGePoint3d& point)
{
	return glm::vec3(point.x, point.y, point.z);
}

OdGePoint3d APIGLConverter::Vec3ToOdGePoint3d(const glm::vec3& vec)
{
	return OdGePoint3d(vec.x, vec.y, vec.z);
}

glm::vec3 APIGLConverter::OdGeVector3dToVec3(const OdGeVector3d& vector)
{
	return glm::vec3(vector.x, vector.y, vector.z);
}
