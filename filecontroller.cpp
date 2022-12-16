#include "filecontroller.h"

FileController::FileController()
{
}


void FileController::logMessage(const QString &s)
{
    m_logger.log(s.toStdString());
}

void FileController::logError(const QString &s)
{
    m_logger.err(s.toStdString());
}

void FileController::logError(const QSqlError &s)
{
    logError(s.text());
}

void FileController::init(const std::string& path)
{
    m_logger.init(path);
}
