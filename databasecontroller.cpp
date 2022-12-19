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

QList<RoleString> DatabaseController::getAllRoles()
{
    return m_db.getAllAccessRights();
}

bool DatabaseController::insert(const RoleString& rs)
{
    return m_db.insert(rs);
}

bool DatabaseController::deleteOne(const RoleString& rs)
{
    return m_db.deleteOne(rs);
}

bool DatabaseController::update(const RoleString& oldData, const RoleString& newData)
{
    return m_db.update(oldData, newData);
}

QList<Group> DatabaseController::getAllGroups()
{
    return m_db.getAllGroups();
}

bool DatabaseController::insert(const Group& g)
{
    return m_db.insert(g);
}

bool DatabaseController::deleteOne(const Group& g)
{
    return m_db.deleteOne(g);
}

bool DatabaseController::update(const Group& oldData, const Group& newData)
{
    return m_db.update(oldData, newData);
}

QList<ContractType> DatabaseController::getAllContractTypes()
{
    return m_db.getAllContractTypes();
}

bool DatabaseController::insert(const ContractType& ct)
{
    return m_db.insert(ct);
}

bool DatabaseController::deleteOne(const ContractType& ct)
{
    return m_db.deleteOne(ct);
}

bool DatabaseController::update(const ContractType &oldData, const ContractType &newData)
{
    return m_db.update(oldData, newData);
}

QList<Document> DatabaseController::getAllDocuments()
{
    return m_db.getAllDocuments();
}

bool DatabaseController::insert(const Document& d)
{
    return m_db.insert(d);
}

bool DatabaseController::deleteOne(const Document& d)
{
    return m_db.deleteOne(d);
}

bool DatabaseController::update(const Document &oldData, const Document &newData)
{
    return m_db.update(oldData, newData);
}

QList<GapYear> DatabaseController::getAllGapYears()
{
    return m_db.getAllGapYears();
}

bool DatabaseController::insert(const GapYear& gy)
{
    return m_db.insert(gy);
}

bool DatabaseController::deleteOne(const GapYear& gy)
{
    return m_db.deleteOne(gy);
}

bool DatabaseController::update(const GapYear &oldData, const GapYear &newData)
{
    return m_db.update(oldData, newData);
}
