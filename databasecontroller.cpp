#include "databasecontroller.h"

#include "user.h"

bool DatabaseController::connect(const DB::Settings& s)
{
    return m_db.connect(s);
}

bool DatabaseController::login(const std::string& login, const std::string& password)
{
    auto ret = m_db.login(login, password);

    if (ret.has_value())
    {
        auto data = User::instance()->data();
        data->email = ret->email;
        data->login = ret->login;
        data->role = ret->role;

        return true;
    }

    return false;
}

QList<UserData> DatabaseController::getAllUsers()
{
    return m_db.getAllUsers();
}

bool DatabaseController::insert(const UserData &d, const QString &password)
{
    return m_db.insert(d, password);
}

bool DatabaseController::deleteOne(const UserData &d)
{
    return m_db.deleteOne(d);
}

bool DatabaseController::update(const UserData& newData, const UserData& userToUpdate, const QString &password)
{
    return m_db.update(newData, userToUpdate, password);
}
