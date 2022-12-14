#pragma once

#include <string>

namespace Log {

class Logger
{
public:
    Logger();
    virtual ~Logger();

    virtual void log(const std::string& s) = 0;
};

} // Log
