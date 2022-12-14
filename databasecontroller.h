#pragma once

#include "database.h"
#include "dbsettings.h"

class DatabaseController final
{
public:
    DatabaseController();

    bool connect(const DB::Settings& s);

private:
    DB::Database m_db;
};

