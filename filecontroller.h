#pragma once

#include "filelogger.h"

class FileController
{
public:
    static FileController* instance()
    {
        static FileController fc;
        return &fc;
    }

    void logMessage(const std::string& s);

private:
    FileController();
    ~FileController() noexcept;
    FileController(const FileController&) = delete;
    FileController(FileController&&) = delete;
    FileController operator=(const FileController&) = delete;

    FileLogger m_logger;
};

#define LOGL(x) FileController::instance()->logMessage(x)

