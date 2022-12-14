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
    void logError(const std::string& s);

private:
    FileController();
    ~FileController() noexcept {};
    FileController(const FileController&) = delete;
    FileController(FileController&&) = delete;
    FileController operator=(const FileController&) = delete;

    Log::FileLogger m_logger;
};

#define fileController FileController::instance()
#define LOGL(x) fileController->logMessage(x)
#define ERR(x) fileController->logError(x)

