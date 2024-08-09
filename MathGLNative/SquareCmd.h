#pragma once
#include "IActionCmd.h"
#include "MathSquare.h"

class SquareCmd : public IActionCmd {
public:
    SquareCmd() : minPnt(0, 0), maxPnt(1, 1), height(1.0) {}

    bool serialize(const std::vector<std::string>& strData) override;
    bool execute() override;

private:
    OdGePoint2d minPnt;
    OdGePoint2d maxPnt;
    double height;
};
