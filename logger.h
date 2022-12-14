#pragma once

#include <string>

namespace Log {

class Logger
{
public:
    Logger() = default;
    virtual ~Logger() = default;

    virtual void log(const std::string& s) = 0;
    virtual void err(const std::string& s) = 0;
};

} // Log
