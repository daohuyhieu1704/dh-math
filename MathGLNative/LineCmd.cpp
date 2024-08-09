#include "pch.h"
#include "LineCmd.h"
#include "GLEngineNative.h"
#include "MathLine.h"

bool LineCmd::execute()
{
    MathLine* line = new MathLine();
    line->setStartPnt(startPnt);
    line->setEndPnt(endPnt);
    GLEngineNative::GetInstance()->m_entities.push_back(line);
    return true;
}

bool LineCmd::serialize(const std::vector<std::string>& strData)
{
	if (strData.size() < 3)
	{
		return false;
	}
    std::vector<std::string> point1Coords = EditorInput::CommandPrompt::split(strData[1], ',');
    std::vector<std::string> point2Coords = EditorInput::CommandPrompt::split(strData[2], ',');

	if (point1Coords.size() != 3 || point2Coords.size() != 3)
    {
		return false;
	}

    startPnt =
    {
    std::stof(point1Coords[0]),
    std::stof(point1Coords[1]),
    std::stof(point1Coords[2])
    };

    endPnt = 
    {
        std::stof(point2Coords[0]),
        std::stof(point2Coords[1]),
        std::stof(point2Coords[2])
    };

	return true;
}
