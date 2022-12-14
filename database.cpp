#include "database.h"

#include <QDebug>

#include "filecontroller.h"

using namespace DB;

Database::Database()
{

}

Database::~Database() noexcept
{
    m_db.close();
}

bool Database::connect(const Settings& s)
{
    if (!isOpen())
    {
        auto db = QSqlDatabase::addDatabase("PSQL");
        db.setHostName("admin");
        db.setDatabaseName("");
        db.setUserName("");
        db.setPassword("");
        m_db = db;

        if (!m_db.open())
        {
            LOGL();
        }
        return m_db.open();
    }

    return false;
}

bool Database::isOpen() const
{
    return m_db.isOpen();
}
