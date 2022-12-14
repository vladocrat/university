#pragma once

#include <memory>

#include "logger.h"

namespace Log {

class FileLogger final : public Logger
{
public:
    FileLogger();
    ~FileLogger();

    void init(const std::string& fileName);
    void log(const std::string& s);
    void err(const std::string& s);
    void reset() noexcept;
    void reset(const std::string& fileName) noexcept;

private:
    struct File;
    std::unique_ptr<File> impl;
};

} //Log
