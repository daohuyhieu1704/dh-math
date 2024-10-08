#include "pch.h"
#include "SquareCmd.h"
#include "GLEngineNative.h"

bool SquareCmd::serialize(const std::vector<std::string>& strData) {
    if (strData.size() != 4) {
		return false;
    }

    std::vector<std::string> minCoords = EditorInput::CommandPrompt::split(strData[1], ',');
    std::vector<std::string> maxCoords = EditorInput::CommandPrompt::split(strData[2], ',');

    if (minCoords.size() != 2 || maxCoords.size() != 2) {
		return false;
    }

    minPnt = {
        std::stof(minCoords[0]),
        std::stof(minCoords[1])
    };

    maxPnt = {
        std::stof(maxCoords[0]),
        std::stof(maxCoords[1])
    };

    height = std::stod(strData[3]);
	return true;
}

bool SquareCmd::execute() {
    MathSquare* square = new MathSquare();
    square->setMinPnt(minPnt);
    square->setMaxPnt(maxPnt);
    square->setHeight(height);

    GLEngineNative::GetInstance()->m_entities.push_back(square);

    return true;
}
