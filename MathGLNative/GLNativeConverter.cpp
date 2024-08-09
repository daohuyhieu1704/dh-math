#include "pch.h"
#include "GLNativeConverter.h"

glm::mat4 GLNativeConverter::ConvertToGlmMat4(const GLdouble modelview[16])
{
    glm::mat4 mat{};

    for (int i = 0; i < 16; ++i)
    {
        mat[i / 4][i % 4] = static_cast<float>(modelview[i]);
    }

    return mat;
}
