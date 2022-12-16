#include "database.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

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
    m_settings = s;

    if (!isOpen())
    {
        auto db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName(s.hostName);
        db.setDatabaseName(s.dbName);
        db.setUserName(s.username);
        db.setPassword(s.password);
        db.setPort(s.port);
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
        ERR(QString::fromStdString("user with login: " + login + " doesn't exist"));
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

QList<UserData> Database::getAllUsers()
{
    QList<UserData> ret;

    if (!isOpen())
    {
        ERR("failed to fetch all users, no connection to db");
        return ret;
    }

    QSqlQuery query;

    if (!query.prepare("SELECT * FROM users"))
    {
        ERR(m_db.lastError());
    }

    auto loginIx = query.record().indexOf("user_login");
    auto emailIx = query.record().indexOf("user_email");
    //TODO add roles

    if (!executeQuery(query))
    {
        return ret;
    }

    QString login;
    QString email;

    while (query.next())
    {
        login = query.value(loginIx).toString();
        email = query.value(emailIx).toString();

        UserData d;
        d.login = login.toStdString();
        d.email = email.toStdString();
        ret.append(d);
    }

    return ret;
}

bool Database::executeQuery(QSqlQuery& query)
{
    if (!query.exec())
    {
        ERR("last query: " + query.executedQuery());
        ERR(m_db.lastError());

        return false;
    }

    return true;

}
