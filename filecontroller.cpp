#include "filecontroller.h"

FileController::FileController()
{
    m_logger.init("log.txt");
}

void FileController::logMessage(const std::string &s)
{
    m_logger.log(s);
}

void FileController::logError(const std::string &s)
{
    m_logger.err(s);
}
