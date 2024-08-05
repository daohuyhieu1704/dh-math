#include "pch.h"
#include "SquareCmd.h"
#include "GLEngineNative.h"

void SquareCmd::serialize(const std::vector<std::string>& strData) {
    if (strData.size() < 4) {
        throw std::runtime_error("Invalid input for SQUARE command");
    }

    std::vector<std::string> minCoords = EditorInput::CommandPrompt::split(strData[1], ',');
    std::vector<std::string> maxCoords = EditorInput::CommandPrompt::split(strData[2], ',');
    if (minCoords.size() != 2 || maxCoords.size() != 2) {
        throw std::runtime_error("Invalid coordinates for SQUARE command");
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
}

bool SquareCmd::execute() {
    MathSquare* square = new MathSquare();
    square->setMinPnt(minPnt);
    square->setMaxPnt(maxPnt);
    square->setHeight(height);

    GLEngineNative::GetInstance()->m_entities.push_back(square->m_renderMethod);

    return true;
}
