#include "userrepository.h"

#include "databasecontroller.h"

void UserRepository::getAll()
{
    auto users = dbController->getAllUsers();

    for (const auto& x : users)
    {
        qDebug() << x.toString();
    }

    qDebug() << m_model.list().count();
    m_model.clear();

    for (const auto& x: users)
    {
        m_model.addUser(x);
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

bool UserRepository::deleteOne(int i)
{
    return dbController->deleteOne(m_model.list().at(i));
}

bool UserRepository::update(const QString& login, const QString& email, const QString& role, const QString& password, int userIx)
{
    UserData ud;
    ud.login = login.toStdString();
    ud.email = email.toStdString();
    ud.role = intToRole(role.toInt());
    auto userToUpdate = m_model.list().at(userIx);

    return dbController->update(ud, userToUpdate, password);
}

int UserRepository::userCount()
{
    return m_model.list().count();
}
