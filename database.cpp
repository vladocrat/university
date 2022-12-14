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
        LOGL("trying to connect to db");

        if (!m_db.open())
        {
            ERR("failed to open connection to db");
        }
        return m_db.open();
    }

    return false;
}

bool Database::isOpen() const
{
    return m_db.isOpen();
}

bool Database::userExists(const std::string& login) const
{
    //TODO
    return false;
}

std::optional<UserData> Database::login(const std::string &login, const std::string &password)
{
    if (!isOpen())
    {
        ERR("database is closed");
        return {};
    }

    UserData d;

    if (!userExists(login))
    {
        ERR("user with login: " + login + " doesn't exist");
    }

    /*d = select * from users where login = login and password = hash(password)
        if (d == null)
        {
            LOGL("user: " << login << " doesn't exist")
            return {};
        }
        d.login = q.login
        d.email = q.email
        d.role = q.role
    */

    return d;
}
