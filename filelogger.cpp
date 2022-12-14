#include "filelogger.h"

#include <fstream>

using namespace Log;

struct FileLogger::File
{
    File(const std::string& fileName)
    {
        file.open(fileName, std::fstream::in | std::fstream::app);
    }

    ~File() noexcept
    {
        file.close();
    }

    std::fstream file;
};

FileLogger::FileLogger()
{

}

FileLogger::~FileLogger()
{

}

void FileLogger::init(const std::string &fileName)
{
    if (!impl)
    {
        impl = std::make_unique<File>(fileName);
    }
}

void FileLogger::reset() noexcept
{
    if (impl)
    {
        impl.reset();
    }
}

void FileLogger::reset(const std::string &fileName) noexcept
{
    reset();
    init(fileName);
}

void FileLogger::log(const std::string &s)
{
    impl->file << s;
}

void FileLogger::err(const std::string &s)
{
    impl->file << "ERR::" << s;
}
