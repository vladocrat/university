#pragma once

#include <QString>
#include <QSqlError>

#include "filelogger.h"

class FileController
{
public:
    static FileController* instance()
    {
        static FileController fc;
        return &fc;
    }

    void logMessage(const QString& s);
    void logError(const QString& s);
    void logError(const QSqlError& s);
    void init(const std::string& path);

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

