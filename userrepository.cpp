#include "userrepository.h"

#include "databasecontroller.h"

void UserRepository::getAll()
{
    auto users = dbController->getAllUsers();

    for (const auto& x: users)
    {
        if (!m_model.list().contains(x))
        {
            m_model.addUser(x);
        }
    }
}

bool UserRepository::insert(const QString& login, const QString& email, const QString& role, const QString& password)
{
    UserData ud;
    ud.login = login.toStdString();
    ud.email = email.toStdString();
    ud.role = intToRole(role.toInt());

    return dbController->insert(ud, password);
}

bool UserRepository::deleteOne(const UserRepository &)
{
    return {};
}

bool UserRepository::update(const UserRepository &)
{
    return {};
}
