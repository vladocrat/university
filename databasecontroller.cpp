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
