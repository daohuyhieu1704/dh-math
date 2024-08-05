#include "pch.h"
#include "CircleCmd.h"
#include <stdexcept>
#include <CommandPrompt.h>
#include "GLEngineNative.h"
#include "MathCircle.h"

void CircleCmd::serialize(const std::vector<std::string>& strData)
{
    if (strData.size() < 3)
    {
        throw std::runtime_error("Invalid input for CIRCLE command");
    }

    std::vector<std::string> centerCoords = EditorInput::CommandPrompt::split(strData[1], ',');
    if (centerCoords.size() != 3) 
    {
        throw std::runtime_error("Invalid center coordinates for CIRCLE command");
    }

    center = {
        std::stof(centerCoords[0]),
        std::stof(centerCoords[1]),
        std::stof(centerCoords[2])
    };

    radius = std::stod(strData[2]);
}

bool CircleCmd::execute()
{
    MathCircle* circle = new MathCircle();
    circle->setCenter(center);
    circle->setRadius(radius);

    GLEngineNative::GetInstance()->m_entities.push_back(circle->m_renderMethod);

    return true;
}
