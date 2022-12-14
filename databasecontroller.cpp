#include "databasecontroller.h"

DatabaseController::DatabaseController()
{
}

bool DatabaseController::connect(const DB::Settings &s)
{
    return m_db.connect(s);
}
