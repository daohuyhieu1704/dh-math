#include "pch.h"
#include "CircleCmd.h"
#include <stdexcept>
#include <CommandPrompt.h>
#include "GLEngineNative.h"
#include "MathCircle.h"

bool CircleCmd::serialize(const std::vector<std::string>& strData)
{
    if (strData.size() < 3)
	{
		return false;
    }

    std::vector<std::string> centerCoords = EditorInput::CommandPrompt::split(strData[1], ',');
    if (centerCoords.size() != 3) 
	{
		return false;
    }

    center = {
        std::stof(centerCoords[0]),
        std::stof(centerCoords[1]),
        std::stof(centerCoords[2])
    };

    radius = std::stod(strData[2]);
    return true;
}

bool CircleCmd::execute()
{
    MathCircle* circle = new MathCircle();
    circle->setCenter(center);
    circle->setRadius(radius);

    GLEngineNative::GetInstance()->m_entities.push_back(circle);

    return true;
}
