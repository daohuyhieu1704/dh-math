#include "pch.h"
#include "OdObjectBase.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <random>
#include <ctime>
#include <string>

std::string OdObjectBase::GetObjectId() const
{
    return m_objectId;
}

std::string OdObjectBase::GenerateShortId()
{
    std::time_t t = std::time(nullptr);
    std::mt19937 rng(static_cast<unsigned int>(t));
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 15);

    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << (t & 0xFFFFFFF);

    for (int i = 0; i < 2; ++i) {
        ss << std::hex << dist(rng);
    }

    return ss.str().substr(0, 8);
}