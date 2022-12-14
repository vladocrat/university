#include "filecontroller.h"

FileController::FileController()
{
    m_logger.init("log.txt");
}

void FileController::logMessage(const std::string &s)
{
    m_logger.log(s);
}
