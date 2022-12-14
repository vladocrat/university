#pragma once

#include <memory>

#include "logger.h"

class FileLogger final : public Log::Logger
{
public:
    FileLogger();

    void init(const std::string& fileName);
    void log(const std::string &s);
    void reset() noexcept;
    void reset(const std::string& fileName) noexcept;

private:
    struct File;
    std::unique_ptr<File> impl;
};
