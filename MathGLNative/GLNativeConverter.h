#pragma once
#include <glm/glm.hpp>

class GLNativeConverter
{
public:
	static glm::mat4 ConvertToGlmMat4(const GLdouble modelview[16]);
};

