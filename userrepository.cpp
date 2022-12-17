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

bool UserRepository::insert(const UserData& ud, const QString& password)
{
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
