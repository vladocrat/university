#pragma once

#include <QString>

namespace DB {

struct Settings
{
    Settings()
    {

    }

    QString username;
    QString dbName;
    QString hostName;
    QString password;
    int port;
};

} // DB
