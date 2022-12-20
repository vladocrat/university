#pragma once

#include <string>
#include <unordered_map>
#include <QString>

enum class Role : int
{
    Admin,
    MRO,
    Accountant
};

struct RoleString {
    QString name;
};

struct RoleHash
{
    std::size_t operator()(Role r) const
    {
        return static_cast<std::size_t>(r);
    }
};

const std::unordered_map<const Role, QString, RoleHash> mapRoleToString
{
    {Role::Admin, QString("admin")},
    {Role::MRO, QString("mro")},
    {Role::Accountant, QString("accountant")}
};

const std::unordered_map<const QString, Role, std::hash<QString>> mapStringToRole
{
    {QString("admin"), Role::Admin},
    {QString("mro"), Role::MRO},
    {QString("accountant"), Role::Accountant}
};

const std::unordered_map<const Role, int, RoleHash> mapRoleToInt
{
    {Role::Admin, 1},
    {Role::MRO, 2},
    {Role::Accountant, 3}
};

const std::unordered_map<const int, Role, std::hash<int>> mapIntToRole
{
    {1, Role::Admin},
    {2, Role::MRO},
    {3, Role::Accountant}
};

inline static Role intToRole(int n)
{
    return mapIntToRole.find(n)->second;
}

inline static int roleToInt(const Role& r)
{
    return mapRoleToInt.find(r)->second;
}

inline static QString roleToString(const Role& r)
{
    return mapRoleToString.find(r)->second;
}

inline static Role stringToRole(const QString& s)
{
    return mapStringToRole.find(s)->second;
}

struct UserData
{
    QString toString() const
    {
        return QString("role: ")
                .append(roleStr())
                .append(" login: ")
                .append(QString::fromStdString(login))
                .append(" email: ")
                .append(QString::fromStdString(email));
    }

    QString roleStr() const
    {
        return roleToString(role);
    }

    int roleInt() const
    {
        return roleToInt(role);
    }

    bool operator==(const UserData& other) const
    {
        if (this->role != other.role)
        {
            return false;
        }

        if (this->login != other.login)
        {
            return false;
        }

        if (this->email != other.email)
        {
            return false;
        }

        return true;
    }

    ~UserData() {

    }

    Role role = Role::Admin;
    std::string login = "none";
    std::string email;
};

#define AdminString roleToString(Role::Admin)
#define MROString roleToString(Role::MRO)
#define AccountantString roleToString(Role::Accountant)
