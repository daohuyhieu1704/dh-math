#include "pch.h"
#include "IActionCmd.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>

IActionCmd::IActionCmd()
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    char buffer[26];
    errno_t err = ctime_s(buffer, sizeof(buffer), &now_c);
    if (err != 0) {
        throw std::runtime_error("Failed to convert time to string");
    }

    m_id = std::string(buffer);
}

std::string IActionCmd::getId() const
{
    return m_id;
}
